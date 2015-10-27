// ----------------------------------------------------------------------------
//
// G Library
//
// http://www.gilgil.net
//
// Copyright (c) Gilbert Lee All rights reserved
//
// ----------------------------------------------------------------------------

#include "gobj.h"

// ----------------------------------------------------------------------------
// GStateObj
// ----------------------------------------------------------------------------
struct GStateObj : GObj {
  ~GStateObj() override;
  bool active();
  virtual bool open();
  virtual bool close();

protected:
  bool active_{false};
};

