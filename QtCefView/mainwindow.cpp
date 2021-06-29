#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QTextCodec>
#include "CefBrowser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webview1=ui->widget_1;
    QString uri=QFileInfo(QCoreApplication::applicationDirPath()+"/test.html").absoluteFilePath();
    //QString uri = "/test.html";
    webview1->loadUrl(uri);


    QString uri2=QFileInfo(QCoreApplication::applicationDirPath()+"/test2.html").absoluteFilePath();
    webview2=ui->widget_2;
    webview2->loadUrl(uri2);


    connect(webview1, SIGNAL(recvRenderMsg(QString)), this, SLOT(RecvJsMsg(QString)));
    connect(webview2, SIGNAL(recvRenderMsg(QString)), this, SLOT(RecvJsMsg(QString)));


   // webview3=ui->widget_3;

	ui->widget_1->hide();
	ui->pushButton1->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton1_clicked()
{
    webview1->SendMsgToPage(ui->lineEdit->text());
}

void MainWindow::on_pushButton2_clicked()
{
    webview2->SendMsgToPage(ui->lineEdit->text());
}

void MainWindow::RecvJsMsg(const QString &msg)
{
    ui->label_webmsg->setText(msg);
}

void MainWindow::on_pushButton_loaduri_clicked()
{
	//if (0 == count) {
	//	m_browser.openUrl("https://h5web-pro.jiaoyoushow.com/h5/aprilFools/aprilFools/index.html?isVideo=true&userId=64744935&isInApp=true&roomId=LP86796318&sessionId=1C284834D7CE587AED853E03492A835C&anchorId=86796318&isPc=true&channel=1&platformId=pc_user&h5Server=https://h5-ddos.1kyou.cn");
	//	count++;
	//}
	//else if (1 == count) {
	//	m_browser.openUrl("https://h5webcdn-pro.1kyou.cn/h5/propShMall/propShMall/index.html?userId=64744935&isInApp=true&roomId=LP86796318&sessionId=1C284834D7CE587AED853E03492A835C&anchorId=86796318&isPc=true&channel=1&platformId=pc_user&h5Server=https://h5-ddos.1kyou.cn");
	//	count = 0;
	//}
	//QCefProcessExit();
	//m_browser = nullptr;
	//m_browser = std::shared_ptr<vBrowser>(new vBrowser());
	m_browser = new vBrowser();
	m_browser->setAttribute(Qt::WA_DeleteOnClose);
	if (m_browser) {
		QString url = ui->lineEdit_url->text();
		m_browser->openUrl(url);
		m_browser->show();
	}
	//m_browser.openUrl("https://www.bilibili.com/video/BV1pA411H7vg?from=search&seid=10147493024578840911");

    //webview3->loadUrl(ui->lineEdit_url->text());
}

void MainWindow::closeEvent(QCloseEvent * event)
{
//	QCefProcessExit();
	qApp->exit(0);
	return __super::closeEvent(event);
}
