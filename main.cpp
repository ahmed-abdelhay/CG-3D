#include <QApplication>
#include "ui/ApplicationMainWindow.h"

int main(int argc, char** argv)
{
    QApplication application(argc, argv);

    ApplicationMainWindow mainWindow;
    mainWindow.showMaximized();

    return application.exec();
}
