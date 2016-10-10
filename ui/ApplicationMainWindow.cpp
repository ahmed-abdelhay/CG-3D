#include "ApplicationMainWindow.h"
#include "OSGWidget.h"
#include "controllers/ApplicationManager.h"
#include "ui_MainWindow.h"

#include <QOpenGLWidget>

ApplicationMainWindow::ApplicationMainWindow(QWidget* fParent, Qt::WindowFlags fFlags)
    : QMainWindow(fParent, fFlags),
      mApplicationManager(new ApplicationManager()),
      mUi(new Ui::MainWindow())
{
    mUi->setupUi(this);
    mRenderingWidget = new OSGWidget(mUi->renderingArea, fFlags);
    mRenderingWidget->resize(mUi->renderingArea->width(), mUi->renderingArea->height());

    if (auto osgRenderingWidget = dynamic_cast<OSGWidget*>(mRenderingWidget))
        osgRenderingWidget->setSceneGraph(mApplicationManager->getSceneGraphRootNode());
}

ApplicationMainWindow::~ApplicationMainWindow()
{
}
