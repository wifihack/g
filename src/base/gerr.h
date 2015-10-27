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
#include <ostream>
#include <QString>

// ----------------------------------------------------------------------------
// GErr
// ----------------------------------------------------------------------------
struct GErr {
  enum {
    GERR_OK = 0,
    GERR_OK_FAIL = -1,
    GERR_OK_UNKNOWN = 1000,
    GERR_OK_NOT_SUPPORTED,
    GERR_OK_VIRTUAL_FUNCTION_CALL,
    GERR_OK_VALUE_IS_NULL,
    GERR_OK_VALUE_IS_NOT_NULL,
  };

  enum {
    NET_CATEGORY = 2000
  };

  virtual ~GErr() {}
  virtual const char* name() = 0;
  virtual int code() = 0;
  virtual QString msg() = 0;
};

std::ostream& operator << (std::ostream& os, GErr& err);
std::ostream& operator << (std::ostream& os, GErr&& err);
std::ostream& operator << (std::ostream& os, GErr* err);

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
  GStdErr() :code_(GERR_OK) {}
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
