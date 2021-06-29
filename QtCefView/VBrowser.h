#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QSharedPointer>
#include <QPushButton>
#include <QDialog>
#include "ui_vBrowser.h"

class vBrowser : public QWidget
{
	Q_OBJECT

public:
	explicit vBrowser(QWidget *parent = 0);
	~vBrowser();

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
