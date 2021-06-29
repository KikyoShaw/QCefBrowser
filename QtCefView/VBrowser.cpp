#include "VBrowser.h"
#include <QJsonDocument>
#include <QJsonObject>
#include "CefBrowser.h"

vBrowser::vBrowser(QWidget *parent)
	:QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);
	//setAttribute(Qt::WA_TranslucentBackground);
//	ui.widget->setAutoFillBackground(true);

	hide();
	//接收Web端的消息
	connect(ui.widget_web, &QCefWebView::recvRenderMsg, this, &vBrowser::parseWebMessage, Qt::UniqueConnection);
	//页面加载完成再显示
	connect(ui.widget_web, &QCefWebView::loadFinished, this, [=](bool status) {
		if (status) {
			show();
			raise();
		}
	}, Qt::UniqueConnection);

	//connect(ui.widget_web, &QCefWebView::exitProcessMessage, this, [=]() {
		//delete this;
		//exit(EXIT_FAILURE);
	//}, Qt::UniqueConnection);
	//设置页面透明
//	ui.webEngineView->page()->setBackgroundColor(Qt::transparent);
	//关闭按钮
	connect(ui.pushButton, &QPushButton::clicked, this, &QWidget::close);
	//Toast窗口
	//Toast状态码发送到H5端
	//connect(vLiveMgr, &VLiveMgr::sigSendToastToJs, this, [=](const QString &code) {
	//	ui.webEngineView->sendToWebPage(code);
	//});
}

vBrowser::~vBrowser()
{
}

void vBrowser::openUrl(const QString & url)
{
	ui.widget_web->loadUrl(url);
	//show();
}

void vBrowser::setToast(const QString & text)
{
	//m_labelToast.setToast(text);
}

void vBrowser::mouseMoveEvent(QMouseEvent * e)
{
	if ((e->buttons() & Qt::LeftButton) && m_bMove) {
		move(e->globalPos() - m_point);//移动窗口
	}
}

void vBrowser::mousePressEvent(QMouseEvent * e)
{
	//鼠标事件中包含“按住的是左键”
	if (e->button() == Qt::LeftButton) {
		m_bMove = true;
		m_point = e->globalPos() - frameGeometry().topLeft();
	}
}

void vBrowser::mouseReleaseEvent(QMouseEvent * e)
{
	m_bMove = false;
}

void vBrowser::closeEvent(QCloseEvent * event)
{
	//QCefProcessExit();
	ui.widget_web->closeBrowser(event);
	return __super::closeEvent(event);
}

void vBrowser::showEvent(QShowEvent *event)
{
	return __super::showEvent(event);
}

void vBrowser::resizeEvent(QResizeEvent *event)
{
	return __super::resizeEvent(event);
}

void vBrowser::parseWebMessage(const QString & message)
{
	//qInfo() << QStringLiteral("活动页面消息:") << message;
	// 解析json格式
	QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());
	if (jsonDoc.isNull()) {
		return;
	}
	if (jsonDoc.isObject()) {
		QJsonObject obj = jsonDoc.object();
		int action = obj.value("action").toInt(-1);
		switch (action)
		{
			/*	case E_WebActionClose: {
					close();
					break;
				}*/
		default:
			break;
		}
	}
}
