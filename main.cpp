#include "ApplicationMain.h"

#include <QApplication>
#include <QDebug>
#include <QLabel>
#include <QPushButton>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    ApplicationMain mainWindow;
    mainWindow.show();
    return app.exec();
}
