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
    OSGWidget(QWidget* fParent = nullptr, Qt::WindowFlags fFlages = 0);

    virtual ~OSGWidget();

    void setSceneGraph(const osg::ref_ptr<osg::Node>& fSceneGraphRootNode);

    void setContext(ApplicationContext *fContext) override;

protected:
    void paintEvent(QPaintEvent* fPaintEvent) override;
    void paintGL() override;
    void resizeGL(int fWidth, int fHeight) override;

    void keyPressEvent(QKeyEvent* fEvent) override;
    void keyReleaseEvent(QKeyEvent* fEvent) override;

    void mouseMoveEvent(QMouseEvent* fEvent) override;
    void mousePressEvent(QMouseEvent* fEvent) override;
    void mouseReleaseEvent(QMouseEvent* fEvent) override;
    void wheelEvent(QWheelEvent* fEvent) override;

    bool event(QEvent* fEvent) override;

private:
    void notifyContainerChanged(const std::shared_ptr<Type> &fObject, ContainerChangeType fChangeType) override;
    void propertyChanged(Type *fSource, const std::string &fPropertyName) override;

    void onHome();
    void onResize(int fWidth, int fHeight);

    osgGA::EventQueue* getEventQueue() const;

    QPolygon mLassoPoints;
    bool mEnableLasso;

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
    osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
    osg::ref_ptr<osg::Node> mSceneGraphRootNode;
};
