#include "ApplicationMain.h"

using namespace std;

ApplicationMain::ApplicationMain(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);  //根据ui设计文件部署界面    我不用这个

	QNetworkProxyFactory::setUseSystemConfiguration(false);
	
	//设置http代理   
	QNetworkProxy net;
	net.setType(QNetworkProxy::HttpProxy);
	net.setHostName("127.0.0.1");
	net.setPort(8099);
	QNetworkProxy::setApplicationProxy(net);

	QString strHome = "http://games.dmm.com/zh-CHS/detail/kancolle/";  //主页
	//QString strHome = "http://www.baidu.com";  //主页
	
	
	//新建url编辑器  其实没有用
	pURLEdit = new QLineEdit(this);
	pURLEdit->setText(strHome);

	//把编辑器放进工具栏
	QToolBar* pToolBar = addToolBar(tr("&URLEdit"));
	pToolBar->addWidget(pURLEdit);
	
	pInspectorAction = new QAction(tr("&Inspector"), this);
	connect(pInspectorAction, &QAction::triggered, this, &ApplicationMain::openInspector);
	QMenu* pInspector = menuBar()->addMenu(tr("&debug"));
	pInspector->addAction(pInspectorAction);


	pMainWebView = new QWebEngineView(this);  //实例化MainWebView
	pMainWebView->load(QUrl(strHome));
	pMainWebView->setMinimumSize(1200, 720);

	pMainWebPage = pMainWebView->page(); 
	connect(pMainWebView, &QWebEngineView::urlChanged,this,&ApplicationMain::onUrlChanged);
	connect(pMainWebPage, &QWebEnginePage::loadFinished, this, &ApplicationMain::PageLoadFinish);

	QWidget* widget = new QWidget;
	widget->setMinimumSize(1200,720);
	this->setCentralWidget(widget);
	QHBoxLayout* layout = new QHBoxLayout(widget);
	
	layout->addWidget(pMainWebView);

	this->setLayout(layout);
	this->statusBar();
}

//析构函数 对象消亡时自动调用
//可用来释放内存空间
ApplicationMain::~ApplicationMain()
{
}

void ApplicationMain::onUrlChanged()
{
	pURLEdit->setText(pMainWebView->url().toString());
}

void ApplicationMain::PageLoadFinish()   //页面加载完毕
{
	Sleep(500);
	pURLEdit->setText(pMainWebView->url().toString());
	//document.getElementById("iframe1").src
	string nowURL = pMainWebView->url().toString().toStdString();
	regex pattern1("redirect", regex::icase);
	regex pattern2("netgame", regex::icase);
	regex pattern3("gadgets", regex::icase);
	regex pattern4("kcs2", regex::icase);
	
	smatch result;
	if (regex_search(nowURL, result, pattern1))
	{
		pMainWebPage->runJavaScript(QString("self.location.href=document.getElementById('game_frame').src;"));
	}
	if (regex_search(nowURL,result, pattern2))
	{
		pMainWebPage->runJavaScript(QString("self.location.href=document.getElementById('game_frame').src;"));
	}
	if (regex_search(nowURL, result, pattern3))
	{
		Sleep(2500);
		pMainWebPage->runJavaScript(QString("self.location.href=document.getElementById('htmlWrap').src;"));
	}
	if (regex_search(nowURL, result, pattern4))
	{
		Sleep(500);
		pMainWebView->setMaximumSize(1200, 720);
		pMainWebPage->runJavaScript(QString("document.getElementsByTagName('body')[0].style = 'margin: 0px; overflow: hidden;'"));
	}
	qDebug() << pMainWebView->url().toString();
}

void ApplicationMain::openInspector() 
{
	QDialog* pInspectorDialog = new QDialog(this);
	pInspectorDialog->setWindowTitle(tr("Inspector"));
	QWebEngineView *pInspectorView = new QWebEngineView(this);
	pInspectorDialog->setMinimumSize(1200, 720);
	QHBoxLayout* pInspectorDialoglayout = new QHBoxLayout(this);
	pInspectorDialoglayout->addWidget(pInspectorView);
	pInspectorDialog->setLayout(pInspectorDialoglayout);
	pMainWebPage->setDevToolsPage(pInspectorView->page());
	pInspectorDialog->show();

}

void ApplicationMain::Sleep(int msec)//延时不阻塞 毫秒
{
	QTime dieTime = QTime::currentTime().addMSecs(msec);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}