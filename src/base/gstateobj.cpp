#include "gstateobj.h"

// ----------------------------------------------------------------------------
// GStageObj
// ----------------------------------------------------------------------------
GStateObj::~GStateObj() {
  if (active_) {
    qWarning() << metaObject()->className() << "active state. call close before entering destructor";
  }
}

bool GStateObj::active() {
  return active_;
}

bool GStateObj::open() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

bool GStateObj::close() {
  SET_ERR(GStdErr(g::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}
