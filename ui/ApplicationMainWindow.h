#pragma once

#include <QWidget>
#include <memory>
#include "ui_ApplicationMainWindow.h"

class ApplicationManager;
class QOpenGLWidget;

class ApplicationMainWindow : public QWidget
{
    Q_OBJECT
public:
    ApplicationMainWindow(QWidget* fParent = nullptr, Qt::WindowFlags fFlags = 0);
    virtual ~ApplicationMainWindow();

private:
    QOpenGLWidget* mRenderingWidget;
    std::unique_ptr<ApplicationManager> mApplicationManager;

    Ui::MainWindow mUi;
};
