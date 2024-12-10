#include "mainwindow.h"
#include <QApplication>
#include "CefBrowser.h"
#include "CefOsrWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//ÀëÆÁäÖÈ¾²âÊÔÊ¾Àı
	/*QCefProcessStartOsr();
    CefOsrWidget w;
    w.show();*/

	//CEFÖ÷´°¿Ú²âÊÔÊ¾Àı
	QCefProcessStart();
	MainWindow w;
	w.show();

	QCefMessageLoop();

	int qt_exit_code = a.exec();
	
	QCefProcessExit();
	return qt_exit_code;
}
