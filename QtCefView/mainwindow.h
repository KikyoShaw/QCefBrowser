#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcefwebview.h"
#include "VBrowser.h"
#include <QSharedPointer>
#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QCefWebView* webview1;

    QCefWebView* webview2;

    QCefWebView* webview3;

private slots:
    void on_pushButton1_clicked();

    void on_pushButton2_clicked();
    void RecvJsMsg(const QString& msg);
    void on_pushButton_loaduri_clicked();

protected:
	void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

	int count = 0;

//	std::shared_ptr<vBrowser> m_browser = nullptr;

	//QSharedPointer<vBrowser> m_browser = nullptr;

	vBrowser *m_browser = nullptr;

	//vBrowser m_browser;
};

#endif // MAINWINDOW_H
