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

#include <QLineEdit>
#include "gpropitem.h"

// ----------------------------------------------------------------------------
// GPropItemLineEdit
// ----------------------------------------------------------------------------
struct GPropItemLineEdit : public GPropItem {
  Q_OBJECT

public:
  GPropItemLineEdit(QTreeWidget* widget, QObject* object, QMetaProperty mpro);
  GPropItemLineEdit(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);

protected:
  QLineEdit* lineEdit_;
};

#endif // QT_GUI_LIB
