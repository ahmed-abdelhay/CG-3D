#include "ApplicationMainWindow.h"
#include "OSGWidget.h"
#include "controllers/ApplicationManager.h"
#include "ui/MeshIOControlWidget.h"
#include "ui/Q3DSurfacesListWidget.h"
#include "ui_MainWindow.h"

#include <QOpenGLWidget>
#include <QListWidget>

ApplicationMainWindow::ApplicationMainWindow(QWidget* fParent, Qt::WindowFlags fFlags)
    : QMainWindow(fParent, fFlags),
      mApplicationManager (new ApplicationManager()),
      mUi(new Ui::MainWindow())
{
    mUi->setupUi(this);
    mRenderingWidget = new OSGWidget(mUi->renderingArea, fFlags);
    mRenderingWidget->resize(mUi->renderingArea->width(), mUi->renderingArea->height());
    mRenderingWidget->update();

    if (auto osgRenderingWidget = dynamic_cast<OSGWidget*>(mRenderingWidget))
        osgRenderingWidget->setSceneGraph(mApplicationManager->getSceneGraphRootNode());

    // add the menu tools
    auto meshIOControlWidget = new MeshIOControlWidget();
    mUi->stackedMenuWidget->addWidget(meshIOControlWidget);
    meshIOControlWidget->setContext(mApplicationManager->context());

    // add the tab tools
    auto surfacesList = new Q3DSurfacesListWidget();
    surfacesList->setContext(mApplicationManager->context());
    QIcon surfcaceListIcon(":/icons/resources/icons/3D objects list.ico");
    mUi->toolsTabWidget->addTab(surfacesList, surfcaceListIcon, "3D Surfaces List");
}

ApplicationMainWindow::~ApplicationMainWindow()
{
}
