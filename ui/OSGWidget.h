#pragma once

#include <QOpenGLWidget>

#include <osg/ref_ptr>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>

#include "infrastructure/ApplicationContextProvider.h"
#include "infrastructure/PropertyChangedHandler.h"
#include "infrastructure/ContainerChangedHandler.h"

class OSGWidget : public QOpenGLWidget, public ApplicationContextProvider,
        public PropertyChangedHandler, public ContainerChangedHandler
{
    Q_OBJECT

public:
    OSGWidget(QWidget* _parent = nullptr, Qt::WindowFlags _flages = 0);

    virtual ~OSGWidget();

    void setSceneGraph(const osg::ref_ptr<osg::Node>& _sceneGraphRootNode);

    void setContext(ApplicationContext *_context) override;

protected:
    void paintEvent(QPaintEvent* _paintEvent) override;
    void paintGL() override;
    void resizeGL(int _width, int _height) override;

    void keyPressEvent(QKeyEvent* _event) override;
    void keyReleaseEvent(QKeyEvent* _event) override;

    void mouseMoveEvent(QMouseEvent* _event) override;
    void mousePressEvent(QMouseEvent* _event) override;
    void mouseReleaseEvent(QMouseEvent* _event) override;
    void wheelEvent(QWheelEvent* _event) override;

    bool event(QEvent* _event) override;

private:
    void notifyContainerChanged(const std::shared_ptr<Type> &_object, ContainerChangeType _changeType) override;
    void propertyChanged(Type *_source, const std::string &_propertyName) override;

    void onHome();
    void onResize(int _width, int _height);

    osgGA::EventQueue* getEventQueue() const;

    QPolygon mLassoPoints;
    bool mIsLassoEnabled;

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
    osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
    osg::ref_ptr<osg::Node> mSceneGraphRootNode;
};
