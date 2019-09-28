#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ApplicationMain.h"
#include <QLineEdit>
#include <regex>
#include <string>
#include <QAction>
#include <QMessageBox>
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>
#include<QDebug>
#include <QFileDialog>
#include <QtWebEngineWidgets/qwebengineview.h>
#include <QtWebEngineWidgets/qwebenginepage.h>
#include <QLineEdit>
#include <QtWebEngine/qquickwebenginescript.h>
#include <QtNetwork/qnetworkproxy.h>
class ApplicationMain : public QMainWindow
{
	Q_OBJECT

public:
	ApplicationMain(QWidget *parent = Q_NULLPTR);
	~ApplicationMain();

private:
	Ui::ApplicationMainClass ui;
	QLineEdit* pURLEdit;
	QWebEngineView* pMainWebView;
	QWebEnginePage* pMainWebPage;
	void ApplicationMain::onUrlChanged();
	void ApplicationMain::PageLoadFinish();
	void ApplicationMain::openInspector();
	QAction* pInspectorAction;
	void ApplicationMain::Sleep(int msec);
};
