#include "ApplicationMainWindow.h"
#include "OSGWidget.h"
#include "ApplicationManager.h"

#include <QOpenGLWidget>
#include <QSpinBox>

ApplicationMainWindow::ApplicationMainWindow(QWidget* fParent, Qt::WindowFlags fFlags)
    : QWidget(fParent, fFlags),
      mRenderingWidget(new OSGWidget(this)),
      mApplicationManager(new ApplicationManager())
{
    mUi.setupUi(this);
    mUi.renderingArea = mRenderingWidget;

    if (auto osgRenderingWidget = dynamic_cast<OSGWidget*>(mRenderingWidget))
            osgRenderingWidget->setSceneGraph(mApplicationManager->getSceneGraphRootNode());


    QWidget *firstPageWidget = new QSpinBox;
    QWidget *secondPageWidget = new QSpinBox;
    QWidget *thirdPageWidget = new QSpinBox;

    mUi.stackedWidget->addWidget(firstPageWidget);
    mUi.stackedWidget->addWidget(secondPageWidget);
    mUi.stackedWidget->addWidget(thirdPageWidget);
}

ApplicationMainWindow::~ApplicationMainWindow()
{
}
