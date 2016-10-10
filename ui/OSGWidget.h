#pragma once

#include <QOpenGLWidget>

#include <osg/ref_ptr>

#include <osgViewer/GraphicsWindow>
#include <osgViewer/CompositeViewer>

class OSGWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OSGWidget(QWidget* parent = nullptr, Qt::WindowFlags f = 0);

    virtual ~OSGWidget();

    void setSceneGraph(const osg::ref_ptr<osg::Node>& fSceneGraphRootNode);

protected:

    virtual void paintEvent( QPaintEvent* paintEvent );
    virtual void paintGL();
    virtual void resizeGL( int width, int height );

    virtual void keyPressEvent( QKeyEvent* event );
    virtual void keyReleaseEvent( QKeyEvent* event );

    virtual void mouseMoveEvent( QMouseEvent* event );
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void mouseReleaseEvent( QMouseEvent* event );
    virtual void wheelEvent( QWheelEvent* event );

    virtual bool event( QEvent* event );

private:

    virtual void onHome();
    virtual void onResize(int width, int height );

    osgGA::EventQueue* getEventQueue() const;

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> mGraphicsWindow;
    osg::ref_ptr<osgViewer::CompositeViewer> mViewer;
    osg::ref_ptr<osg::Node> mSceneGraphRootNode;
};
