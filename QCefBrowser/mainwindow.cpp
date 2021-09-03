#include "mainwindow.h"
#include <QDir>
#include <QTextCodec>
#include "QCefBrowser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    QString uri = QFileInfo(QCoreApplication::applicationDirPath()+"/test.html").absoluteFilePath();
    ui.widget_html->loadUrl(uri);

	ui.widget_web->ModifyZoom(10);

    connect(ui.widget_html, &QCefWebView::recvRenderMsg, this, &MainWindow::sltRecvJsMsg);
	connect(ui.pushButton_toJs, &QPushButton::clicked, this, &MainWindow::sltSendMsgToJs);
	connect(ui.pushButton_load, &QPushButton::clicked, this, &MainWindow::sltLoadUrlWed);
	connect(ui.pushButton_test, &QPushButton::clicked, this, &MainWindow::sltLoadTestWeb);
	connect(ui.pushButton_zoom, &QPushButton::clicked, this, &MainWindow::sltZoomWeb);
}

MainWindow::~MainWindow()
{
}

void MainWindow::sltRecvJsMsg(const QString &msg)
{
    ui.label_webmsg->setText(msg);
}

void MainWindow::sltSendMsgToJs()
{
	QString text = ui.lineEdit->text();
	ui.widget_html->SendMsgToPage(text);
}

void MainWindow::sltLoadUrlWed()
{
	QString text = ui.lineEdit->text();
	ui.widget_web->loadUrl(text);
}

void MainWindow::sltLoadTestWeb()
{
	m_browser = new QCefBrowser();
	m_browser->setAttribute(Qt::WA_DeleteOnClose);
	if (m_browser) {
		//QString url = ui->lineEdit_url->text();
		QString url = "https://www.bilibili.com/video/BV1pA411H7vg?from=search&seid=10147493024578840911";
		m_browser->openUrl(url);
		m_browser->show();
	}
}

void MainWindow::sltZoomWeb()
{
	ui.widget_web->ModifyZoom(0.1);
}
