#pragma once

#include "ui_ApplicationMain.h"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QNetworkProxy>
#include <QSlider>
#include <QSpinBox>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QWebEngineView>

class ApplicationMain : public QMainWindow
{
    Q_OBJECT

public:
    ApplicationMain(QWidget* parent = Q_NULLPTR);
    ~ApplicationMain();

private:
    Ui::ApplicationMainClass ui;
    QLineEdit* pURLEdit;
    QWebEngineView* pMainWebView;
    QWebEnginePage* pMainWebPage;
    void onUrlChanged();
    void PageLoadFinish();
    void openInspector();
    QAction* pInspectorAction;
    void Sleep(int msec);
};
