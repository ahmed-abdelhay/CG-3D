#pragma once

#include <QMainWindow>
#include <memory>

class ApplicationManager;
class OSGWidget;
namespace Ui{ class MainWindow;}

class ApplicationMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ApplicationMainWindow(QWidget* _parent = nullptr, Qt::WindowFlags _flags = 0);
    virtual ~ApplicationMainWindow();

private:
    enum class ToolsTabsNames: int
    {
        SURFACS_LIST_TAB = 0
    };

    OSGWidget* mRenderingWidget;
    std::unique_ptr<ApplicationManager> mApplicationManager;

    Ui::MainWindow* mUi;
};
