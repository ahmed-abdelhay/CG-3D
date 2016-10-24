#include "OSGWidget.h"

#include <OpenMesh/Core/Geometry/VectorT.hh>

#include <osg/Camera>

#include <osg/Geode>

#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include <stdexcept>
#include <vector>

#include <QKeyEvent>
#include <QPainter>
#include <QWheelEvent>

#include "infrastructure/Type.h"
#include "infrastructure/ApplicationContext.h"
#include "modelObjects/PolygonalLasso.h"
#include "events/AddLassoPointEvent.h"
#include "events/ApplyLassoEvent.h"

OSGWidget::OSGWidget(QWidget* _parent, Qt::WindowFlags _flages)
    : QOpenGLWidget(_parent, _flages),
      mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(x(), y(), _parent->width(), _parent->height())),
      mViewer(new osgViewer::CompositeViewer),
      mIsLassoEnabled(false)
{
    auto aspectRatio = width() / static_cast<float>(height());

    osg::Camera* camera = new osg::Camera;
    camera->setViewport(x(), y(), width(), height());
    camera->setClearColor(osg::Vec4( 0.9f, 0.9f, 0.9f, 1.f ) );
    camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 1.f, 1000.f);
    camera->setGraphicsContext(mGraphicsWindow);

    osgViewer::View* view = new osgViewer::View;
    view->setCamera(camera);
    view->addEventHandler(new osgViewer::StatsHandler);

    osgGA::TrackballManipulator* manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow( false );

    view->setCameraManipulator( manipulator );

    mViewer->addView( view );
    mViewer->setThreadingModel(osgViewer::CompositeViewer::SingleThreaded);
    mViewer->realize();

    // This ensures that the widget will receive keyboard events. This focus
    // policy is not set by default. The default, Qt::NoFocus, will result in
    // keyboard events that are ignored.
    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(width(), height());

    // Ensures that the widget receives mouse move events even though no
    // mouse button has been pressed. We require this in order to let the
    // graphics window switch viewports properly.
    setMouseTracking(true);
}

OSGWidget::~OSGWidget()
{
    if (mContext)
    {
        unsubscribePropertyChangedOnType(PolygonalLassoType, mContext);
        unsubscribeToContainerChanged(mContext);
    }
}

void OSGWidget::setSceneGraph(const osg::ref_ptr<osg::Node> &_sceneGraphRootNode)
{
    mSceneGraphRootNode = _sceneGraphRootNode;
    mViewer->getView(0)->setSceneData(mSceneGraphRootNode);
}

void OSGWidget::setContext(ApplicationContext *_context)
{
    mContext = _context;
    subscribePropertyChangedOnType(PolygonalLassoType, mContext);
    subscribeToContainerChanged(mContext);
}

void OSGWidget::paintEvent(QPaintEvent* _paintEvent)
{
    this->makeCurrent();
    this->paintGL();

    if (mIsLassoEnabled)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::transparent);
        painter.drawPolygon(mLassoPoints);
        painter.end();
    }

    this->doneCurrent();
}

void OSGWidget::paintGL()
{
    mViewer->frame();
}

void OSGWidget::resizeGL(int _width, int _height)
{
    this->getEventQueue()->windowResize( this->x(), this->y(), _width, _height);
    mGraphicsWindow->resized(this->x(), this->y(), _width, _height);

    this->onResize(_width, _height);
}

void OSGWidget::keyPressEvent(QKeyEvent* _event)
{
    QString keyString   = _event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    if( _event->key() == Qt::Key_H )
    {
        this->onHome();
        return;
    }

    if (mIsLassoEnabled)
    {
        if (_event->key() == Qt::Key_Enter || _event->key() == Qt::Key_Return)
        {
            auto event = std::make_shared<ApplyLassoEvent>();
            std::vector<osg::Camera*> cameras;
            mViewer->getCameras(cameras);
            event->viewMatrix = cameras[0]->getViewMatrix();
            event->projectionMatrix = cameras[0]->getProjectionMatrix();
            mContext->publish(event);
            return;
        }
    }

    this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::keyReleaseEvent(QKeyEvent* _event)
{
    QString keyString   = _event->text();
    const char* keyData = keyString.toLocal8Bit().data();

    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::mouseMoveEvent(QMouseEvent* _event)
{
    this->getEventQueue()->mouseMotion(static_cast<float>(_event->x()),
                                       static_cast<float>(_event->y()));
}

void OSGWidget::mousePressEvent(QMouseEvent* _event)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch(_event->button())
    {
    case Qt::LeftButton:
        button = 1;
        if (mIsLassoEnabled)
        {
            auto addPointEvent = std::make_shared<AddLassoPointEvent>();
            addPointEvent->lassoPoint = OpenMesh::Vec3f(_event->x() / static_cast<float>(width()), _event->y() / static_cast<float>(height()), 0);
            mContext->publish(addPointEvent);
        }
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    this->getEventQueue()->mouseButtonPress( static_cast<float>(_event->x()),
                                             static_cast<float>(_event->y()),
                                             button);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* _event)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch(_event->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;

    case Qt::MiddleButton:
        button = 2;
        break;

    case Qt::RightButton:
        button = 3;
        break;

    default:
        break;
    }

    this->getEventQueue()->mouseButtonRelease( static_cast<float>(_event->x()),
                                               static_cast<float>(_event->y()),
                                               button );
}

void OSGWidget::wheelEvent(QWheelEvent* _event)
{
    _event->accept();
    int delta = _event->delta();

    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                                 : osgGA::GUIEventAdapter::SCROLL_DOWN;

    this->getEventQueue()->mouseScroll( motion );
}

bool OSGWidget::event(QEvent* _event)
{
    bool handled = QOpenGLWidget::event(_event);

    // This ensures that the OSG widget is always going to be repainted after the
    // user performed some interaction. Doing this in the event handler ensures
    // that we don't forget about some event and prevents duplicate code.
    switch(_event->type())
    {
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
    case QEvent::Wheel:
        this->update();
        break;

    default:
        break;
    }

    return handled;
}

void OSGWidget::notifyContainerChanged(const std::shared_ptr<Type> &_object, ContainerChangeType _changeType)
{
    update();
    if (_object->metaObject()->className() == PolygonalLassoType)
    {
        if (_changeType == ContainerChangeType::OBJECT_ADDED)
        {
            mIsLassoEnabled = true;
        }
        else
        {
            mIsLassoEnabled = false;
            mLassoPoints.clear();
        }
    }
    else if (_object->metaObject()->className() == ThreeDObjectType)
    {
        onHome();
    }
}

void OSGWidget::propertyChanged(Type *_source, const std::string &_propertyName)
{
    if (_source->metaObject()->className() == PolygonalLassoType)
    {
        if (_propertyName == LassoPointsType)
        {
            if (auto lasso = dynamic_cast<PolygonalLasso*>(_source))
            {
                mLassoPoints.clear();
                for (const auto point : lasso->getPoints())
                    mLassoPoints.push_back(QPoint(point[0]* width(), point[1] * height()));
            }
        }
    }
}

void OSGWidget::onHome()
{
    osgViewer::ViewerBase::Views views;
    mViewer->getViews( views );

    for( std::size_t i = 0; i < views.size(); i++ )
    {
        osgViewer::View* view = views.at(i);
        view->home();
    }
}

void OSGWidget::onResize(int _width, int _height)
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras(cameras);
    cameras[0]->setViewport(x(), y(), _width, _height);
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}
