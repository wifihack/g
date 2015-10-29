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

#include "gcapture.h"

// ----------------------------------------------------------------------------
// GPcap
// ----------------------------------------------------------------------------
struct GPcap : GCapture {
  Q_OBJECT
  Q_PROPERTY(QString dev         MEMBER dev_)
  Q_PROPERTY(QString filter      MEMBER filter_)
  Q_PROPERTY(int     snapLen     MEMBER snapLen_)
  Q_PROPERTY(int     flags       MEMBER flags_)
  Q_PROPERTY(int     readTimeout MEMBER readTimeout_)

public:
  enum {
    ERROR_IN_PCAP_NEXT_EX,
  };

public:
  QString dev_{"eth0"};// gilgil temp 2015.10.28
  QString filter_{""};
  int     snapLen_{65536}; // gilgil temp 2015.10.28
  int     flags_{1}; // PCAP_OPENFLAG_PROMISCUOUS
  int     readTimeout_{1};

public:
  GPcap(QObject* parent = nullptr) : GCapture(parent) {}
  ~GPcap() override;

protected:
  bool doOpen() override;
  bool doClose() override;

public:
  Result read(GPacket* packet) override;
  Result write(GPacket* packet) override;
  Result relay(GPacket* packet) override;

  PathType captureType() { return OutOfPath; }
  int dataLink() { return dataLink_; }

protected:
  bool pcapProcessFilter(pcap_if_t* dev);

  pcap_t*  pcap_{nullptr};
  int dataLink_{DLT_NULL};
};
