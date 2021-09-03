/********************************************************************************
** Form generated from reading UI file 'QCefBrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QCEFBROWSER_H
#define UI_QCEFBROWSER_H

#include <QCefWebView.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_vBrowser
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QWidget *widget;
    QPushButton *pushButton;
    QCefWebView *widget_web;

    void setupUi(QWidget *vBrowser)
    {
        if (vBrowser->objectName().isEmpty())
            vBrowser->setObjectName(QString::fromUtf8("vBrowser"));
        vBrowser->resize(505, 729);
        vBrowser->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"color:white;\n"
"background-color: rgba(0, 0, 0, 70%);\n"
"border-radius:8px;\n"
"font: 16px Microsoft YaHei;\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	border-image: url(:/Prank/Prank/ic_gb.png);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	border-image: url(:/Prank/Prank/ic_gb_bright.png);\n"
"}"));
        verticalLayout = new QVBoxLayout(vBrowser);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(vBrowser);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("#frame\n"
"{\n"
"	border-radius:8px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 505, 100));
        widget->setMinimumSize(QSize(0, 100));
        widget->setStyleSheet(QString::fromUtf8("#widget{\n"
"border-image: url(:/QSimpleBrowser/qrc/web.png);\n"
"}"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(455, 16, 32, 32));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("#pushButton\n"
"{\n"
"	border-image: url(:/QCefBrowser/qrc/ic_zggb.png);\n"
"}\n"
"\n"
"#pushButton:hover\n"
"{\n"
"	border-image: url(:/QCefBrowser/qrc/ic_zggb1.png);\n"
"}"));
        widget_web = new QCefWebView(frame);
        widget_web->setObjectName(QString::fromUtf8("widget_web"));
        widget_web->setGeometry(QRect(0, 0, 505, 729));
        widget_web->raise();
        widget->raise();
        pushButton->raise();

        verticalLayout->addWidget(frame);


        retranslateUi(vBrowser);

        QMetaObject::connectSlotsByName(vBrowser);
    } // setupUi

    void retranslateUi(QWidget *vBrowser)
    {
        vBrowser->setWindowTitle(QApplication::translate("vBrowser", "\346\264\273\345\212\250\351\241\265\351\235\242", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class vBrowser: public Ui_vBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QCEFBROWSER_H
