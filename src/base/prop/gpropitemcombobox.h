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

#include <QComboBox>
#include "gpropitem.h"

// ----------------------------------------------------------------------------
// GPropItemEnum
// ----------------------------------------------------------------------------
struct GPropItemComboBox : public GPropItem {
  GPropItemComboBox(QTreeWidgetItem* parent, QObject* object, QMetaProperty mpro);

protected:
  QComboBox* comboBox_{nullptr};
};

#endif // QT_GUI_LIB
