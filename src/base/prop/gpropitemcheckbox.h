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
// GPropItemCheckBox
// ----------------------------------------------------------------------------
struct GPropItemCheckBox : public GPropItem {
  GPropItemCheckBox(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);

protected:
  QCheckBox* checkBox_{nullptr};
};

#endif // QT_GUI_LIB
