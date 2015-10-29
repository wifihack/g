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

#include "gpackethdr.h"
#ifdef WIN32
#include <windivert/windivert.h>
#endif // WIN32

// ----------------------------------------------------------------------------
// GFlowValue
// ----------------------------------------------------------------------------
class GFlowValue
{
public:
  size_t         packets;
  size_t         bytes;
  struct timeval ts;
  bool           created;
  uint8_t*       totalMem;
};

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
  GPktHdr* pktHdr;
  uint8_t* pktData;

  //
  // datalink layer
  //
  int      linkType; // DLT_EN10MB, ...
  GEthHdr* ethHdr;

  //
  // network layer
  //
  uint16_t netType; // ETHERTYPE_IP, ETHERTYPE_ARP, ...
  GIpHdr*  ipHdr;
  GArpHdr* arpHdr;

  //
  // transport layer(protocol)
  //
  uint8_t   proto; // IPPROTO_TCP, IPPROTO_UDP, IPPROTO_ICMP, ...
  GTcpHdr*  tcpHdr;
  GUdpHdr*  udpHdr;
  GIcmpHdr* icmpHdr;

  //
  // data
  //
  uint8_t* data;
  int      dataLen;

  //
  // control
  //
  bool drop;

  //
  // flow
  //
  void*       flowKey; // GMacFlowKey, GIpFlowKey, GTcpFlowKey, GUdpFlowKey, ...
  GFlowValue* flowValue;

#ifdef WIN32
  WINDIVERT_ADDRESS divertAddr;
#endif // WIN32

public:
  void parse();
  void clear();
};
