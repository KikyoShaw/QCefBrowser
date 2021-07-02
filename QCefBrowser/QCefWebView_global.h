#ifndef QCEFWEBVIEW_GLOBAL_H
#define QCEFWEBVIEW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QCEFWEBVIEW_LIBRARY)
#  define QCEFWEBVIEWSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QCEFWEBVIEWSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QCEFWEBVIEW_GLOBAL_H
