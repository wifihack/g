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

#include <errno.h>
//#include <ostream>
#include <QDebug>
#include <QString>

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  enum {
    OK = 0,
    FAIL = -1,
    UNKNOWN = 1000,
    NOT_SUPPORTED,
    NOT_OPENED_STATE,
    NOT_CLOSED_STATE,
    VIRTUAL_FUNCTION_CALL,
    VALUE_IS_NULL,
    VALUE_IS_NOT_NULL,
    RETURN_NULL,
    RETURN_NOT_NULL,
  };

  enum {
    NET_CATEGORY = 2000
  };

  virtual ~GErr() {}
  virtual const char* name() = 0;
  virtual int code() = 0;
  virtual QString msg() = 0;
};

// ----- gilgil temp 2015.10.28 -----
/*
std::ostream& operator << (std::ostream& os, GErr& err);
std::ostream& operator << (std::ostream& os, GErr&& err);
std::ostream& operator << (std::ostream& os, GErr* err);
*/
QDebug operator << (QDebug os, GErr& err);
QDebug operator << (QDebug os, GErr&& err);
QDebug operator << (QDebug os, GErr* err);
// ----------------------------------

// ----------------------------------------------------------------------------
// GLastErr
// ----------------------------------------------------------------------------
struct GLastErr : GErr {
  GLastErr() : code_(errno) {}

  const char* name() override { return "LastErr"; }
  int code() override { return code_; }
  QString msg() override { return strerror(code_); }

  void setCode(int code) { code_ = code; }

protected:
  int code_;
};

// ----------------------------------------------------------------------------
// GStdErr
// ----------------------------------------------------------------------------
struct GStdErr : GErr {
  GStdErr() : code_(OK) {}
  GStdErr(int code) : code_(code) {}
  GStdErr(int code, QString msg) : code_(code), msg_(msg) {}

  const char* name() override { return "StdErr"; }
  int code() override { return code_; }
  QString msg() override { return msg_; }

  void setCode(int code) { code_ = code; }
  void setMsg(QString msg) { msg_ = msg; }

protected:
  int code_;
  QString msg_;
};
