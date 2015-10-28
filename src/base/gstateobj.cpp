#include "gstateobj.h"

// ----------------------------------------------------------------------------
// GStageObj
// ----------------------------------------------------------------------------
GStateObj::~GStateObj() {
  if (state_ != Closed) {
    qCritical() << QString("%1 State is %2. close must be called in descendant of GStateObject").arg(metaObject()->className()).arg((int)state_);
  }
}

bool GStateObj::active() {
  return state_ == Opened;
}

bool GStateObj::open() {
  if (state_ != Closed) {
    SET_ERR(GStdErr(GErr::NOT_CLOSED_STATE, QString("%1 State is %2").arg(metaObject()->className()).arg((int)state_)));
    return false;
  }

  bool res = doOpen();
  state_ = Opening;
  if (!res) {
    state_ = Closing;
    doClose();
    state_ = Closed;
    return false;
  }

  state_ = Opened;
  emit opened();
  return true;
}

bool GStateObj::close() {
  if (state_ == Closed)
    return true;

  if (!active()) {
    SET_ERR(GStdErr(GErr::NOT_OPENED_STATE, QString("%1 State is %2").arg(metaObject()->className()).arg((int)state_)));
    return false;
  }

  state_ = Closing;
  doClose();
  state_ = Closed;
  emit closed();
  return true;
}

bool GStateObj::doOpen() {
  SET_ERR(GStdErr(GErr::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}

bool GStateObj::doClose() {
  SET_ERR(GStdErr(GErr::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return false;
}
