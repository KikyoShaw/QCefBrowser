#pragma once

#include <QtWidgets/QWidget>
#include <QMouseEvent>
#include <QSharedPointer>
#include <QPushButton>
#include "ui_QCefBrowser.h"

class QCefBrowser : public QWidget
{
    Q_OBJECT

public:
    QCefBrowser(QWidget *parent = Q_NULLPTR);
	~QCefBrowser();

	void openUrl(const QString &url);
	//œ‘ ætoast
	void setToast(const QString& text);

protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void closeEvent(QCloseEvent *event);
	virtual void showEvent(QShowEvent *event);
	virtual void resizeEvent(QResizeEvent *event);

private:
	void parseWebMessage(const QString &message);

private:
    Ui::vBrowser ui;
	QPoint m_point;
	bool m_bMove = false;
	QSharedPointer<QWidget> topWidget = nullptr;
};

