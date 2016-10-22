#pragma once

#include <QWidget>

#include "infrastructure/ApplicationContextProvider.h"

namespace Ui {class MeshIOControlWidget;}
class ApplicationContext;

class MeshIOControlWidget : public QWidget, public ApplicationContextProvider
{
    Q_OBJECT
public:
    MeshIOControlWidget(QWidget *_parent = nullptr);
    virtual ~MeshIOControlWidget();

    void setContext(ApplicationContext *_context);

public slots:
    void on_actionLoadMeshClicked_triggered();
    void on_actionSaveMeshClicked_triggered();
    void on_actionDeleteMeshClicked_triggered();

private:
    Ui::MeshIOControlWidget* mUi;
};
