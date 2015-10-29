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

// ----------------------------------------------------------------------------
// GMacKey
// ----------------------------------------------------------------------------
class GMacKey
{
public:
  GMac mac;

  bool operator < (const GMacKey& rhs) const;
};

// ----------------------------------------------------------------------------
// GMacFlowKey
// ----------------------------------------------------------------------------
class GMacFlowKey
{
public:
  GMac srcMac;
  GMac dstMac;

  bool operator < (const GMacFlowKey& rhs) const;
  GMacFlowKey reverse();
};

// ----------------------------------------------------------------------------
// GMacSessionKey
// ----------------------------------------------------------------------------
class GMacSessionKey
{
public:
  GMac mac1;
  GMac mac2;

  bool operator < (const GMacSessionKey& rhs) const;
};

// ----------------------------------------------------------------------------
// GIpKey
// ----------------------------------------------------------------------------
class GIpKey
{
public:
  GIp ip;

  bool operator < (const GIpKey& rhs) const;
};

// ----------------------------------------------------------------------------
// GIpFlowKey
// ----------------------------------------------------------------------------
class GIpFlowKey
{
public:
  GIp srcIp;
  GIp dstIp;

  bool operator < (const GIpFlowKey& rhs) const;
  GIpFlowKey reverse();
};

// ----------------------------------------------------------------------------
// GIpSessionKey
// ----------------------------------------------------------------------------
class GIpSessionKey
{
public:
  GIp ip1;
  GIp ip2;

  bool operator < (const GIpSessionKey& rhs) const;
};

// ----------------------------------------------------------------------------
// GPortKey
// ----------------------------------------------------------------------------
class GPortKey
{
public:
  int port;

  bool operator < (const GPortKey& rhs) const;
};

// ----------------------------------------------------------------------------
// GPortFlowKey
// ----------------------------------------------------------------------------
class GPortFlowKey
{
public:
  uint16_t srcPort;
  uint16_t dstPort;

  bool operator < (const GPortFlowKey& rhs) const;
  GPortFlowKey reverse();
};

// ----------------------------------------------------------------------------
// GPortSessionKey
// ----------------------------------------------------------------------------
class GPortSessionKey
{
public:
  uint16_t port1;
  uint16_t port2;

  bool operator < (const GPortSessionKey& rhs) const;
};

// ----------------------------------------------------------------------------
// GTransportKey
// ----------------------------------------------------------------------------
class GTransportKey
{
public:
  GIp     ip;
  uint16_t port;

  bool operator < (const GTransportKey& rhs) const;
};

typedef GTransportKey GTcpKey;
typedef GTransportKey GUdpKey;

// ----------------------------------------------------------------------------
// GTransportFlowKey
// ----------------------------------------------------------------------------
class GTransportFlowKey
{
public:
  GIp     srcIp;
  uint16_t srcPort;
  GIp     dstIp;
  uint16_t dstPort;

  bool operator < (const GTransportFlowKey& rhs) const;
  bool operator == (const GTransportFlowKey& rhs) const;
  GTransportFlowKey reverse();
};

typedef GTransportFlowKey GTcpFlowKey;
typedef GTransportFlowKey GUdpFlowKey;

// ----------------------------------------------------------------------------
// GTransportSessionKey
// ----------------------------------------------------------------------------
class GTransportSessionKey
{
public:
  GIp     ip1;
  uint16_t port1;
  GIp     ip2;
  uint16_t port2;

  bool operator < (const GTransportSessionKey& rhs) const;
};

typedef GTransportSessionKey GTcpSessionKey;
typedef GTransportSessionKey GUdpSessionKey;

// ----------------------------------------------------------------------------
// GTupleFlowKey
// ----------------------------------------------------------------------------
class GTupleFlowKey
{
public:
  uint8_t                 proto;
  GTransportFlowKey flow;

  bool operator < (const GTupleFlowKey& rhs) const;
  GTupleFlowKey reverse();
};
