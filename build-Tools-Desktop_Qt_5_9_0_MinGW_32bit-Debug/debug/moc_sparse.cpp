/****************************************************************************
** Meta object code from reading C++ file 'sparse.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Tools/sparse.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sparse.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_sparse_t {
    QByteArrayData data[8];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_sparse_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_sparse_t qt_meta_stringdata_sparse = {
    {
QT_MOC_LITERAL(0, 0, 6), // "sparse"
QT_MOC_LITERAL(1, 7, 25), // "on_pushButtonFind_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 27), // "on_lineEdit_editingFinished"
QT_MOC_LITERAL(4, 62, 27), // "on_pushButton_clear_clicked"
QT_MOC_LITERAL(5, 90, 27), // "on_pushButton_Parse_clicked"
QT_MOC_LITERAL(6, 118, 24), // "on_pushButtonAdd_clicked"
QT_MOC_LITERAL(7, 143, 24) // "on_pushButtonDel_clicked"

    },
    "sparse\0on_pushButtonFind_clicked\0\0"
    "on_lineEdit_editingFinished\0"
    "on_pushButton_clear_clicked\0"
    "on_pushButton_Parse_clicked\0"
    "on_pushButtonAdd_clicked\0"
    "on_pushButtonDel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_sparse[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void sparse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        sparse *_t = static_cast<sparse *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_pushButtonFind_clicked(); break;
        case 1: _t->on_lineEdit_editingFinished(); break;
        case 2: _t->on_pushButton_clear_clicked(); break;
        case 3: _t->on_pushButton_Parse_clicked(); break;
        case 4: _t->on_pushButtonAdd_clicked(); break;
        case 5: _t->on_pushButtonDel_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject sparse::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_sparse.data,
      qt_meta_data_sparse,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *sparse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *sparse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_sparse.stringdata0))
        return static_cast<void*>(const_cast< sparse*>(this));
    return QWidget::qt_metacast(_clname);
}

int sparse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
