#include "ApplicationMain.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include<QDebug>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	ApplicationMain mainWindow;
	mainWindow.show();
	return app.exec();
}
