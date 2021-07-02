/****************************************************************************
** Meta object code from reading C++ file 'QCefWebView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QCefWebView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCefWebView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QCefWebView_t {
    QByteArrayData data[22];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCefWebView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCefWebView_t qt_meta_stringdata_QCefWebView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QCefWebView"
QT_MOC_LITERAL(1, 12, 12), // "titleChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "title"
QT_MOC_LITERAL(4, 32, 10), // "urlChanged"
QT_MOC_LITERAL(5, 43, 3), // "url"
QT_MOC_LITERAL(6, 47, 16), // "loadStateChanged"
QT_MOC_LITERAL(7, 64, 9), // "isLoading"
QT_MOC_LITERAL(8, 74, 9), // "canGoBack"
QT_MOC_LITERAL(9, 84, 12), // "canGoForward"
QT_MOC_LITERAL(10, 97, 15), // "webViewGotFocus"
QT_MOC_LITERAL(11, 113, 13), // "recvRenderMsg"
QT_MOC_LITERAL(12, 127, 3), // "msg"
QT_MOC_LITERAL(13, 131, 11), // "loadStarted"
QT_MOC_LITERAL(14, 143, 12), // "loadFinished"
QT_MOC_LITERAL(15, 156, 11), // "loadSuccess"
QT_MOC_LITERAL(16, 168, 7), // "loadUrl"
QT_MOC_LITERAL(17, 176, 4), // "back"
QT_MOC_LITERAL(18, 181, 7), // "forward"
QT_MOC_LITERAL(19, 189, 7), // "refresh"
QT_MOC_LITERAL(20, 197, 4), // "stop"
QT_MOC_LITERAL(21, 202, 16) // "onBrowserCreated"

    },
    "QCefWebView\0titleChanged\0\0title\0"
    "urlChanged\0url\0loadStateChanged\0"
    "isLoading\0canGoBack\0canGoForward\0"
    "webViewGotFocus\0recvRenderMsg\0msg\0"
    "loadStarted\0loadFinished\0loadSuccess\0"
    "loadUrl\0back\0forward\0refresh\0stop\0"
    "onBrowserCreated"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCefWebView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    3,   85,    2, 0x06 /* Public */,
      10,    0,   92,    2, 0x06 /* Public */,
      11,    1,   93,    2, 0x06 /* Public */,
      13,    0,   96,    2, 0x06 /* Public */,
      14,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,  100,    2, 0x0a /* Public */,
      17,    0,  103,    2, 0x0a /* Public */,
      18,    0,  104,    2, 0x0a /* Public */,
      19,    0,  105,    2, 0x0a /* Public */,
      20,    0,  106,    2, 0x0a /* Public */,
      21,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,

 // slots: parameters
    QMetaType::Void, QMetaType::QUrl,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QCefWebView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QCefWebView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->titleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->urlChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->loadStateChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->webViewGotFocus(); break;
        case 4: _t->recvRenderMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->loadStarted(); break;
        case 6: _t->loadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->loadUrl((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 8: _t->back(); break;
        case 9: _t->forward(); break;
        case 10: _t->refresh(); break;
        case 11: _t->stop(); break;
        case 12: _t->onBrowserCreated(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QCefWebView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::titleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QCefWebView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::urlChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QCefWebView::*)(bool , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::loadStateChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QCefWebView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::webViewGotFocus)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QCefWebView::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::recvRenderMsg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QCefWebView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::loadStarted)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QCefWebView::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QCefWebView::loadFinished)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QCefWebView::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_QCefWebView.data,
    qt_meta_data_QCefWebView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QCefWebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCefWebView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QCefWebView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int QCefWebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void QCefWebView::titleChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCefWebView::urlChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCefWebView::loadStateChanged(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QCefWebView::webViewGotFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QCefWebView::recvRenderMsg(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCefWebView::loadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void QCefWebView::loadFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
