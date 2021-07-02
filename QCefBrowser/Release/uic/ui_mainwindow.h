/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcefwebview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame_js;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_sendJs;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_sendToJs;
    QLabel *label;
    QLabel *label_webmsg;
    QCefWebView *widget_html;
    QFrame *frame_web;
    QVBoxLayout *verticalLayout;
    QWidget *widget_find;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_url;
    QPushButton *pushButton_loaduri;
    QPushButton *pushButton_test;
    QCefWebView *widget_web;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1201, 834);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_js = new QFrame(centralWidget);
        frame_js->setObjectName(QString::fromUtf8("frame_js"));
        frame_js->setMinimumSize(QSize(400, 0));
        frame_js->setMaximumSize(QSize(400, 16777215));
        frame_js->setFrameShape(QFrame::StyledPanel);
        frame_js->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_js);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_sendJs = new QWidget(frame_js);
        widget_sendJs->setObjectName(QString::fromUtf8("widget_sendJs"));
        widget_sendJs->setMinimumSize(QSize(0, 50));
        widget_sendJs->setMaximumSize(QSize(16777215, 50));
        horizontalLayout_2 = new QHBoxLayout(widget_sendJs);
        horizontalLayout_2->setSpacing(8);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(10, 0, 10, 0);
        lineEdit = new QLineEdit(widget_sendJs);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setMaximumSize(QSize(16777215, 30));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton_sendToJs = new QPushButton(widget_sendJs);
        pushButton_sendToJs->setObjectName(QString::fromUtf8("pushButton_sendToJs"));
        pushButton_sendToJs->setMinimumSize(QSize(80, 30));
        pushButton_sendToJs->setMaximumSize(QSize(80, 30));
        pushButton_sendToJs->setStyleSheet(QString::fromUtf8("border:1px solid #555;"));

        horizontalLayout_2->addWidget(pushButton_sendToJs);

        label = new QLabel(widget_sendJs);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        label_webmsg = new QLabel(widget_sendJs);
        label_webmsg->setObjectName(QString::fromUtf8("label_webmsg"));

        horizontalLayout_2->addWidget(label_webmsg);


        verticalLayout_2->addWidget(widget_sendJs);

        widget_html = new QCefWebView(frame_js);
        widget_html->setObjectName(QString::fromUtf8("widget_html"));
        widget_html->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(widget_html);


        horizontalLayout_3->addWidget(frame_js);

        frame_web = new QFrame(centralWidget);
        frame_web->setObjectName(QString::fromUtf8("frame_web"));
        frame_web->setFrameShape(QFrame::StyledPanel);
        frame_web->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_web);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_find = new QWidget(frame_web);
        widget_find->setObjectName(QString::fromUtf8("widget_find"));
        widget_find->setMinimumSize(QSize(0, 50));
        widget_find->setMaximumSize(QSize(16777215, 50));
        widget_find->setStyleSheet(QString::fromUtf8("border:1px solid #555;"));
        horizontalLayout = new QHBoxLayout(widget_find);
        horizontalLayout->setSpacing(8);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, 0, 10, 0);
        lineEdit_url = new QLineEdit(widget_find);
        lineEdit_url->setObjectName(QString::fromUtf8("lineEdit_url"));
        lineEdit_url->setMinimumSize(QSize(0, 30));
        lineEdit_url->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(lineEdit_url);

        pushButton_loaduri = new QPushButton(widget_find);
        pushButton_loaduri->setObjectName(QString::fromUtf8("pushButton_loaduri"));
        pushButton_loaduri->setMinimumSize(QSize(60, 30));
        pushButton_loaduri->setMaximumSize(QSize(60, 30));

        horizontalLayout->addWidget(pushButton_loaduri);

        pushButton_test = new QPushButton(widget_find);
        pushButton_test->setObjectName(QString::fromUtf8("pushButton_test"));
        pushButton_test->setMinimumSize(QSize(80, 30));
        pushButton_test->setMaximumSize(QSize(80, 30));

        horizontalLayout->addWidget(pushButton_test);


        verticalLayout->addWidget(widget_find);

        widget_web = new QCefWebView(frame_web);
        widget_web->setObjectName(QString::fromUtf8("widget_web"));
        widget_web->setStyleSheet(QString::fromUtf8("border:1px solid #555;"));

        verticalLayout->addWidget(widget_web);


        horizontalLayout_3->addWidget(frame_web);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1201, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "qceflibtest", nullptr));
        pushButton_sendToJs->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201\345\210\260web\347\253\257", nullptr));
        label->setText(QApplication::translate("MainWindow", "\346\216\245\345\217\227Web\346\225\260\346\215\256\357\274\232", nullptr));
        label_webmsg->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lineEdit_url->setText(QApplication::translate("MainWindow", "http://www.baidu.com", nullptr));
        pushButton_loaduri->setText(QApplication::translate("MainWindow", "\345\212\240\350\275\275\347\275\221\351\241\265", nullptr));
        pushButton_test->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\265\213\350\257\225web", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
