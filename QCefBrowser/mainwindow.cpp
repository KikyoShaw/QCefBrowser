#include "mainwindow.h"
#include <QDir>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    QString uri = QFileInfo(QCoreApplication::applicationDirPath()+"/test.html").absoluteFilePath();
    ui.widget_html->loadUrl(uri);


    connect(ui.widget_html, SIGNAL(recvRenderMsg(QString)), this, SLOT(RecvJsMsg(QString)));
	//connect(ui.pushButton_sendToJs, &QPushButton::clicked, this, &MainWindow::on_pushButton_sendToJs_clicked);
	//connect(ui.pushButton_loaduri, &QPushButton::clicked, this, &MainWindow::on_pushButton_loaduri_clicked);
	connect(ui.pushButton_test, &QPushButton::clicked, this, &MainWindow::on_pushButton_loadTest_clicked);
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButton_sendToJs_clicked()
{
	QString text = ui.lineEdit->text();
    ui.widget_html->SendMsgToPage(text);
}

void MainWindow::RecvJsMsg(const QString &msg)
{
    ui.label_webmsg->setText(msg);
}

void MainWindow::on_pushButton_loaduri_clicked()
{
	QString text = ui.lineEdit->text();
	ui.widget_web->loadUrl(text);
}

void MainWindow::on_pushButton_loadTest_clicked()
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

void MainWindow::resizeEvent(QResizeEvent * event)
{
	//ui.widget_web->
}
