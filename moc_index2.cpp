/****************************************************************************
** Meta object code from reading C++ file 'index2.h'
**
** Created: Tue Oct 26 21:54:19 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "index2.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'index2.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_index2[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x0a,
      25,    7,    7,    7, 0x0a,
      51,    7,    7,    7, 0x0a,
      72,    7,    7,    7, 0x0a,
      84,    7,    7,    7, 0x0a,
     104,    7,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_index2[] = {
    "index2\0\0usemoneybutton()\0"
    "usemoneyunlimitedbutton()\0"
    "usemoneystopbutton()\0clearstat()\0"
    "changeFactoryInfo()\0init()\0"
};

const QMetaObject index2::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_index2,
      qt_meta_data_index2, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &index2::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *index2::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *index2::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_index2))
        return static_cast<void*>(const_cast< index2*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int index2::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: usemoneybutton(); break;
        case 1: usemoneyunlimitedbutton(); break;
        case 2: usemoneystopbutton(); break;
        case 3: clearstat(); break;
        case 4: changeFactoryInfo(); break;
        case 5: init(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
