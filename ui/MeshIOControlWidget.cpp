#include "MeshIOControlWidget.h"

#include <QFileDialog>
#include <QString>

#include "infrastructure/ApplicationContext.h"
#include "ui_MeshIOControlWidtet.h"
#include "events/Read3DObjectEvent.h"
#include "events/Write3DObjectEvent.h"

MeshIOControlWidget::MeshIOControlWidget(QWidget *parent)
    : QWidget(parent),
      mUi(new Ui::MeshIOControlWidget())
{
    mUi->setupUi(this);
}

MeshIOControlWidget::~MeshIOControlWidget()
{}

void MeshIOControlWidget::setContext(ApplicationContext *fContext)
{
    mContext = fContext;
}

void MeshIOControlWidget::on_actionLoadMeshClicked_triggered()
{
    QString meshFilesFilter = tr("3D files (*.stl *.ply *.off)");
    auto fileName = QFileDialog::getOpenFileName(this,
           tr("Load 3D object"), "/home", meshFilesFilter);

    auto loadMeshEvent = std::make_shared<Read3DObjectEvent>();
    loadMeshEvent->meshFileName = fileName.toStdString();
    mContext->publish(loadMeshEvent);
}

void MeshIOControlWidget::on_actionSaveMeshClicked_triggered()
{
    auto writeMeshEvent = std::make_shared<Write3DObjectEvent>();

    mContext->publish(writeMeshEvent);
}
