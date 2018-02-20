/****************************************************************************
** Meta object code from reading C++ file 'Autobot.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../project/Autobot.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Autobot.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Autobot_t {
    QByteArrayData data[9];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Autobot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Autobot_t qt_meta_stringdata_Autobot = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Autobot"
QT_MOC_LITERAL(1, 8, 10), // "accelerate"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 10), // "decelerate"
QT_MOC_LITERAL(4, 31, 11), // "rotate_left"
QT_MOC_LITERAL(5, 43, 12), // "rotate_right"
QT_MOC_LITERAL(6, 56, 9), // "updateCar"
QT_MOC_LITERAL(7, 66, 6), // "rotate"
QT_MOC_LITERAL(8, 73, 7) // "advance"

    },
    "Autobot\0accelerate\0\0decelerate\0"
    "rotate_left\0rotate_right\0updateCar\0"
    "rotate\0advance"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Autobot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Autobot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Autobot *_t = static_cast<Autobot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->accelerate(); break;
        case 1: _t->decelerate(); break;
        case 2: _t->rotate_left(); break;
        case 3: _t->rotate_right(); break;
        case 4: _t->updateCar(); break;
        case 5: _t->rotate(); break;
        case 6: _t->advance(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Autobot::staticMetaObject = {
    { &QGraphicsObject::staticMetaObject, qt_meta_stringdata_Autobot.data,
      qt_meta_data_Autobot,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Autobot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Autobot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Autobot.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsObject::qt_metacast(_clname);
}

int Autobot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
