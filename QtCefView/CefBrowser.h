#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "QCefWebView.h"
QCEFWEBVIEWSHARED_EXPORT int QCefProcessStart();
QCEFWEBVIEWSHARED_EXPORT void QCefMessageLoop();
QCEFWEBVIEWSHARED_EXPORT void QCefProcessExit();
