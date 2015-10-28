// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#include <QList>
#include "gjson.h"

// ----------------------------------------------------------------------------
// QList<int>
// ----------------------------------------------------------------------------
QJsonValueRef operator << (QJsonValueRef ref, const QList<int>& intList);
QJsonValueRef operator >> (const QJsonValueRef ref, QList<int>& intList);

// ----------------------------------------------------------------------------
// GObj
// ----------------------------------------------------------------------------
class GObj;
QJsonValueRef operator << (QJsonValueRef ref, const GObj& obj);
QJsonValueRef operator >> (QJsonValueRef ref, GObj& obj);

#ifdef QT_GUI_LIB

// ----------------------------------------------------------------------------
// QSplitter
// ----------------------------------------------------------------------------
#include <QSplitter>
QJsonValueRef operator << (QJsonValueRef ref, const QSplitter* splitter);
QJsonValueRef operator >> (QJsonValueRef ref, QSplitter* splitter);

// ----------------------------------------------------------------------------
// QWidget
// ----------------------------------------------------------------------------
#include <QWidget>
QJsonValueRef operator << (const QJsonValueRef ref, const QWidget* widget);
QJsonValueRef operator >> (QJsonValueRef ref, QWidget* widget);

#endif // QT_GUI_LIB
