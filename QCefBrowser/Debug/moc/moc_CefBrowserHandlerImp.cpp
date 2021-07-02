/****************************************************************************
** Meta object code from reading C++ file 'CefBrowserHandlerImp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CefBrowserHandlerImp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CefBrowserHandlerImp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CefBrowserHandlerImp_t {
    QByteArrayData data[17];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CefBrowserHandlerImp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CefBrowserHandlerImp_t qt_meta_stringdata_CefBrowserHandlerImp = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CefBrowserHandlerImp"
QT_MOC_LITERAL(1, 21, 14), // "browserCreated"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 10), // "urlChanged"
QT_MOC_LITERAL(4, 48, 3), // "url"
QT_MOC_LITERAL(5, 52, 12), // "titleChanged"
QT_MOC_LITERAL(6, 65, 5), // "title"
QT_MOC_LITERAL(7, 71, 19), // "loadingStateChanged"
QT_MOC_LITERAL(8, 91, 9), // "isLoading"
QT_MOC_LITERAL(9, 101, 9), // "canGoBack"
QT_MOC_LITERAL(10, 111, 12), // "canGoForward"
QT_MOC_LITERAL(11, 124, 15), // "webViewGotFocus"
QT_MOC_LITERAL(12, 140, 13), // "recvRenderMsg"
QT_MOC_LITERAL(13, 154, 3), // "msg"
QT_MOC_LITERAL(14, 158, 11), // "loadStarted"
QT_MOC_LITERAL(15, 170, 12), // "loadFinished"
QT_MOC_LITERAL(16, 183, 11) // "loadSuccess"

    },
    "CefBrowserHandlerImp\0browserCreated\0"
    "\0urlChanged\0url\0titleChanged\0title\0"
    "loadingStateChanged\0isLoading\0canGoBack\0"
    "canGoForward\0webViewGotFocus\0recvRenderMsg\0"
    "msg\0loadStarted\0loadFinished\0loadSuccess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CefBrowserHandlerImp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    1,   55,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,
       7,    3,   61,    2, 0x06 /* Public */,
      11,    0,   68,    2, 0x06 /* Public */,
      12,    1,   69,    2, 0x06 /* Public */,
      14,    0,   72,    2, 0x06 /* Public */,
      15,    1,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    8,    9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,

       0        // eod
};

void CefBrowserHandlerImp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CefBrowserHandlerImp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->browserCreated(); break;
        case 1: _t->urlChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->titleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->loadingStateChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 4: _t->webViewGotFocus(); break;
        case 5: _t->recvRenderMsg((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->loadStarted(); break;
        case 7: _t->loadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CefBrowserHandlerImp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::browserCreated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::urlChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::titleChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)(bool , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::loadingStateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::webViewGotFocus)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::recvRenderMsg)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::loadStarted)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (CefBrowserHandlerImp::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CefBrowserHandlerImp::loadFinished)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CefBrowserHandlerImp::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CefBrowserHandlerImp.data,
    qt_meta_data_CefBrowserHandlerImp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CefBrowserHandlerImp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CefBrowserHandlerImp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CefBrowserHandlerImp.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CefClient"))
        return static_cast< CefClient*>(this);
    if (!strcmp(_clname, "CefDisplayHandler"))
        return static_cast< CefDisplayHandler*>(this);
    if (!strcmp(_clname, "CefLifeSpanHandler"))
        return static_cast< CefLifeSpanHandler*>(this);
    if (!strcmp(_clname, "CefFocusHandler"))
        return static_cast< CefFocusHandler*>(this);
    if (!strcmp(_clname, "CefLoadHandler"))
        return static_cast< CefLoadHandler*>(this);
    if (!strcmp(_clname, "CefRenderHandler"))
        return static_cast< CefRenderHandler*>(this);
    return QObject::qt_metacast(_clname);
}

int CefBrowserHandlerImp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CefBrowserHandlerImp::browserCreated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void CefBrowserHandlerImp::urlChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CefBrowserHandlerImp::titleChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CefBrowserHandlerImp::loadingStateChanged(bool _t1, bool _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CefBrowserHandlerImp::webViewGotFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void CefBrowserHandlerImp::recvRenderMsg(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CefBrowserHandlerImp::loadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void CefBrowserHandlerImp::loadFinished(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
