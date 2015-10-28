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
#ifdef QT_GUI_LIB
#include <QWidget>
#endif // QT_GUI_LIB
#include "gjson.h"

// ----------------------------------------------------------------------------
// operator
// ----------------------------------------------------------------------------
QJsonValueRef& operator << (QJsonValueRef&& ref, const QList<int>& intList);
QJsonValueRef& operator >> (const QJsonValueRef&& ref, QList<int>& intList);

class GObj;
QJsonValueRef& operator << (QJsonValueRef&& ref, const GObj& obj);
QJsonValueRef& operator >> (const QJsonValueRef&& ref, GObj& obj);
QJsonObject& operator << (QJsonObject& json, const GObj& obj);
QJsonObject& operator >> (const QJsonObject& json, GObj& obj);

#ifdef QT_GUI_LIB
QJsonValueRef& operator << (QJsonValueRef&& ref, const QWidget& widget);
QJsonValueRef& operator >> (const QJsonValueRef&& ref, QWidget& widget);
QJsonObject& operator << (QJsonObject& json, const QWidget& widget);
QJsonObject& operator >> (const QJsonObject& json, QWidget& widget);
#endif // QT_GUI_LIB
