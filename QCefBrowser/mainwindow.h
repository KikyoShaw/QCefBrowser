#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "qcefwebview.h"
#include "QCefBrowser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_sendToJs_clicked();
    void RecvJsMsg(const QString& msg);
    void on_pushButton_loaduri_clicked();
	void on_pushButton_loadTest_clicked();

private:
    Ui::MainWindow ui;
	QCefBrowser *m_browser = nullptr;
};

#endif // MAINWINDOW_H
