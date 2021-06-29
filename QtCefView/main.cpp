#include "mainwindow.h"
#include <QApplication>
#include "CefBrowser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCefProcessStart();
    MainWindow w;
    w.show();

	QCefMessageLoop();

    int qt_exit_code = a.exec();
    //
    QCefProcessExit();
    return qt_exit_code;
}
