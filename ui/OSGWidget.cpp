#include "OSGWidget.h"

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

OSGWidget::OSGWidget(QWidget* fParent, Qt::WindowFlags fFlages)
    : QOpenGLWidget(fParent, fFlages),
      mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(x(), y(), fParent->width(), fParent->height())),
      mViewer(new osgViewer::CompositeViewer),
      mEnableLasso(false)
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

void OSGWidget::setSceneGraph(const osg::ref_ptr<osg::Node> &fSceneGraphRootNode)
{
    mSceneGraphRootNode = fSceneGraphRootNode;
    mViewer->getView(0)->setSceneData(mSceneGraphRootNode);
}

void OSGWidget::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
    subscribePropertyChangedOnType(PolygonalLassoType, mContext);
    subscribeToContainerChanged(mContext);
}

void OSGWidget::paintEvent(QPaintEvent* fPaintEvent)
{
    this->makeCurrent();
    this->paintGL();

    if (mEnableLasso)
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

void OSGWidget::resizeGL(int fWidth, int fHeight)
{
    this->getEventQueue()->windowResize( this->x(), this->y(), fWidth, fHeight);
    mGraphicsWindow->resized(this->x(), this->y(), fWidth, fHeight);

    this->onResize(fWidth, fHeight);
}

void OSGWidget::keyPressEvent(QKeyEvent* fEvent)
{
    QString keyString   = fEvent->text();
    const char* keyData = keyString.toLocal8Bit().data();

    if( fEvent->key() == Qt::Key_H )
    {
        this->onHome();
        return;
    }

    this->getEventQueue()->keyPress(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::keyReleaseEvent(QKeyEvent* fEvent)
{
    QString keyString   = fEvent->text();
    const char* keyData = keyString.toLocal8Bit().data();

    this->getEventQueue()->keyRelease(osgGA::GUIEventAdapter::KeySymbol(*keyData));
}

void OSGWidget::mouseMoveEvent(QMouseEvent* fEvent)
{
    this->getEventQueue()->mouseMotion(static_cast<float>(fEvent->x()),
                                       static_cast<float>(fEvent->y()));
}

void OSGWidget::mousePressEvent(QMouseEvent* fEvent)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch(fEvent->button())
    {
    case Qt::LeftButton:
        button = 1;
        if (mEnableLasso)
        {
            auto addPointEvent = std::make_shared<AddLassoPointEvent>();
            addPointEvent->lassoPoint = QPoint(fEvent->x(), fEvent->y());
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

    this->getEventQueue()->mouseButtonPress( static_cast<float>(fEvent->x()),
                                             static_cast<float>(fEvent->y()),
                                             button);
}

void OSGWidget::mouseReleaseEvent(QMouseEvent* fEvent)
{
    // 1 = left mouse button
    // 2 = middle mouse button
    // 3 = right mouse button

    unsigned int button = 0;

    switch(fEvent->button())
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

    this->getEventQueue()->mouseButtonRelease( static_cast<float>(fEvent->x()),
                                               static_cast<float>(fEvent->y()),
                                               button );
}

void OSGWidget::wheelEvent(QWheelEvent* fEvent)
{
    fEvent->accept();
    int delta = fEvent->delta();

    osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                                 : osgGA::GUIEventAdapter::SCROLL_DOWN;

    this->getEventQueue()->mouseScroll( motion );
}

bool OSGWidget::event(QEvent* fEvent)
{
    bool handled = QOpenGLWidget::event(fEvent);

    // This ensures that the OSG widget is always going to be repainted after the
    // user performed some interaction. Doing this in the event handler ensures
    // that we don't forget about some event and prevents duplicate code.
    switch(fEvent->type())
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

void OSGWidget::notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType)
{
    if (fObject->metaObject()->className() == PolygonalLassoType)
    {
        if (fChangeType == ContainerChangeType::OBJECT_ADDED)
        {
            mEnableLasso = true;
        }
        else
        {
            mEnableLasso = false;
            mLassoPoints.clear();
            update();
        }
    }
    else if (fObject->metaObject()->className() == ThreeDObjectType)
    {
        onHome();
    }
}

void OSGWidget::propertyChanged(Type *fSource, const std::string &fPropertyName)
{
    if (fSource->metaObject()->className() == PolygonalLassoType)
    {
        if (fPropertyName == LassoPointsType)
        {
            if (auto lasso = dynamic_cast<PolygonalLasso*>(fSource))
            {
                mLassoPoints.push_back(lasso->getPoints().back());
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

void OSGWidget::onResize(int fWidth, int fHeight)
{
    std::vector<osg::Camera*> cameras;
    mViewer->getCameras(cameras);
    cameras[0]->setViewport(x(), y(), fWidth, fHeight);
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
    osgGA::EventQueue* eventQueue = mGraphicsWindow->getEventQueue();

    if( eventQueue )
        return eventQueue;
    else
        throw std::runtime_error( "Unable to obtain valid event queue");
}
