/****************************************************************************
** Meta object code from reading C++ file 'GLViewer.h'
**
** Created: Sun Apr 27 00:03:51 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../GLViewer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GLViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GLViewer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   10,    9,    9, 0x0a,
      33,   31,    9,    9, 0x0a,
      65,   31,    9,    9, 0x0a,
      87,   31,    9,    9, 0x0a,
     115,   31,    9,    9, 0x0a,
     141,  135,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GLViewer[] = {
    "GLViewer\0\0b\0setWireframe(bool)\0m\0"
    "setRenderingMode(RenderingMode)\0"
    "setRenderingMode(int)\0setDisplayMode(DisplayMode)\0"
    "setDisplayMode(int)\0image\0setRayImage(QImage)\0"
};

void GLViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        GLViewer *_t = static_cast<GLViewer *>(_o);
        switch (_id) {
        case 0: _t->setWireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setRenderingMode((*reinterpret_cast< RenderingMode(*)>(_a[1]))); break;
        case 2: _t->setRenderingMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setDisplayMode((*reinterpret_cast< DisplayMode(*)>(_a[1]))); break;
        case 4: _t->setDisplayMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setRayImage((*reinterpret_cast< const QImage(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData GLViewer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject GLViewer::staticMetaObject = {
    { &QGLViewer::staticMetaObject, qt_meta_stringdata_GLViewer,
      qt_meta_data_GLViewer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &GLViewer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *GLViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *GLViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GLViewer))
        return static_cast<void*>(const_cast< GLViewer*>(this));
    return QGLViewer::qt_metacast(_clname);
}

int GLViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLViewer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
