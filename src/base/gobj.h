// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#pragma once

#include <QDebug>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QSharedPointer>
#include "gbase.h"
#include "gerr.h"
#include "base/prop/gpropitem.h"

// ----------------------------------------------------------------------------
// GObj
// ----------------------------------------------------------------------------
struct GObj : QObject {
  Q_OBJECT

public:
  GObj(QObject* parent = nullptr) : QObject(parent) {}
  ~GObj() override;

  virtual void load(QJsonObject json);
  virtual void save(QJsonObject& json);

  virtual bool load(QJsonObject json, QMetaProperty mpro);
  virtual bool save(QJsonObject& json, QMetaProperty mpro);

#ifdef QT_GUI_LIB
  virtual void createPropItems(QTreeWidgetItem* parent);
  virtual GPropItem* createPropItem(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);
#endif // QT_GUI_LIB

  QSharedPointer<GErr> err{nullptr};
};

// ----------------------------------------------------------------------------
// SET_ERR
// ----------------------------------------------------------------------------
#define SET_ERR(VALUE) { \
  if (err == nullptr) { \
    err = QSharedPointer<GErr>(new VALUE); \
    qWarning() << err; \
  } \
}
