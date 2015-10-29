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

#include "base/gstateobj.h"
#include "base/gthread.h"
#include "net/packet/gpacket.h"

// ----------------------------------------------------------------------------
// GCaptureThread
// ----------------------------------------------------------------------------
struct GCaptureThread : GThread {
  GCaptureThread(QObject* parent = nullptr) : GThread(parent) {}

protected:
  virtual void run();
};

// ----------------------------------------------------------------------------
// GCapture
// ----------------------------------------------------------------------------
struct GCapture : GStateObj {
  Q_OBJECT
  Q_PROPERTY(bool enabled MEMBER enabled_)
  Q_PROPERTY(bool autoRead MEMBER autoRead_)
  Q_PROPERTY(bool autoParse MEMBER autoParse_)

public:
  bool enabled_{true};
  bool autoRead_{true};
  bool autoParse_{true};

public:
  friend class GCaptureThread;

  typedef enum {
    InPath,
    OutOfPath
  } PathType;

  typedef enum {
    Eof = -2,
    Fail = -1,
    TimeOut = 0,
    Ok = 1,
  } Result;

public:
  GCapture(QObject* parent = nullptr) : GStateObj(parent) {}
  ~GCapture() override;

protected:
  bool doOpen() override;
  bool doClose() override;

public:
  virtual Result read(GPacket* packet);
  virtual Result write(GPacket* packet);
  virtual Result relay(GPacket* packet);

  virtual PathType pathType() { return OutOfPath; }
  virtual int dataLink() { return DLT_NULL; }

signals:
  void captured(GPacket* packet);

protected:
  GCaptureThread thread_{this};
  virtual void run();
};
