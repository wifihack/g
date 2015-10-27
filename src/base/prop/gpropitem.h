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

#ifdef QT_GUI_LIB

#include <QDebug>
#include <QMetaProperty>
#include <QJsonObject>
#include <QTreeWidgetItem>

// ----------------------------------------------------------------------------
// GPropItem
// ----------------------------------------------------------------------------
struct GPropItem : public QObject {
  Q_OBJECT

public:
  GPropItem(QTreeWidget* widget, QObject* object, QMetaProperty mpro);
  GPropItem(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);
  virtual void update() = 0;

  QTreeWidgetItem* item_;
  QObject* object_;
  QMetaProperty mpro_;
};

#endif // QT_GUI_LIB
