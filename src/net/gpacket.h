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

#include <pcap.h>

// ----------------------------------------------------------------------------
// GPacket
// ----------------------------------------------------------------------------
struct GCapture;
struct GPacket {
  //
  // info
  //
  GCapture* capture;

  //
  // packet
  //
  pcap_pkthdr* pktHdr;
  u_char* pktData;


  void parse();
  void clear();
};
