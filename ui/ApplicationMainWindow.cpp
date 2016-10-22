#include "ApplicationMainWindow.h"
#include "OSGWidget.h"
#include "controllers/ApplicationManager.h"
#include "ui/MeshIOControlWidget.h"
#include "ui/Q3DSurfacesListWidget.h"
#include "ui/LassoToolsWidget.h"
#include "ui_MainWindow.h"

#include <QListWidget>
#include <QMdiSubWindow>

ApplicationMainWindow::ApplicationMainWindow(QWidget* _parent, Qt::WindowFlags _flags)
    : QMainWindow(_parent, _flags),
      mApplicationManager (new ApplicationManager()),
      mRenderingWidget(new OSGWidget(this, _flags)),
      mUi(new Ui::MainWindow())
{
    mUi->setupUi(this);

    auto renderingSubWindow = mUi->renderingArea->addSubWindow(mRenderingWidget);
    renderingSubWindow->showMaximized();

    mRenderingWidget->setContext(mApplicationManager->context());
    mRenderingWidget->update();

    if (auto osgRenderingWidget = dynamic_cast<OSGWidget*>(mRenderingWidget))
        osgRenderingWidget->setSceneGraph(mApplicationManager->getSceneGraphRootNode());

    // add the menu tools
    auto meshIOControlWidget = new MeshIOControlWidget();
    mUi->toolWidgetsLayout->addWidget(meshIOControlWidget);
    meshIOControlWidget->setContext(mApplicationManager->context());

    auto lassoToolsWidget = new LassoToolsWidget();
    mUi->toolWidgetsLayout->addWidget(lassoToolsWidget);
    lassoToolsWidget->setContext(mApplicationManager->context());

    mUi->toolWidgetsLayout->addSpacerItem(new QSpacerItem(1,1, QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));

    // add the tab tools
    auto surfacesList = new Q3DSurfacesListWidget();
    surfacesList->setContext(mApplicationManager->context());
    QIcon surfcaceListIcon(":/icons/resources/icons/3D objects list.ico");
    mUi->toolsTabWidget->addTab(surfacesList, surfcaceListIcon, "3D Surfaces List");
}

ApplicationMainWindow::~ApplicationMainWindow()
{
}
