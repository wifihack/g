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

#include <QCheckBox>
#include "gpropitem.h"

// ----------------------------------------------------------------------------
// GPropItemUnknownType
// ----------------------------------------------------------------------------
struct GPropItemUnknownType : public GPropItem {
  Q_OBJECT

public:
  GPropItemUnknownType(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);
  void update() override {}
};

#endif // QT_GUI_LIB
