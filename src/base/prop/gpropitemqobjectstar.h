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

#include "gpropitem.h"

// ----------------------------------------------------------------------------
// GPropItemQObjectStar
// ----------------------------------------------------------------------------
struct GPropItemQObjectStar : public GPropItem {
  Q_OBJECT

public:
  GPropItemQObjectStar(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);
  void update() override {}
};

#endif // QT_GUI_LIB
