#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

class CefOsrWidget;
class QCefBrowser;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sltRecvJsMsg(const QString& msg);
	void sltSendMsgToJs();
	void sltLoadUrlWed();
	void sltLoadTestWeb();
	void sltZoomWeb();
	void sltLoadWebp();
	void sltLoadOsr();

private:
    Ui::MainWindow ui;
	QCefBrowser *m_browser = Q_NULLPTR;

	CefOsrWidget* m_osrWidget = Q_NULLPTR;
};

#endif // MAINWINDOW_H
