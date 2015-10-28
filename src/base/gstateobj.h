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
  Q_OBJECT

public:
  typedef enum {
    Closed,
    Opening,
    Opened,
    Closing
  } State;

  ~GStateObj() override;

  bool active();
  virtual bool open();
  virtual bool close();

signals:
  void opened();
  void closed();

protected:
  virtual bool doOpen();
  virtual bool doClose();

private:
  State state_{Closed};
};

