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

#include <QTreeWidget>
#include "base/gobj.h"

// ----------------------------------------------------------------------------
// GPropWidget
// ----------------------------------------------------------------------------
struct GPropWidget : public QTreeWidget {
  GPropWidget(QWidget *parent = 0);
  ~GPropWidget() override;

public:
  QObject* object();
  void setObject(GObj* obj);

protected:
  GObj* obj_;
};

#endif // QT_GUI_LIB
