#include "gpacketkey.h"

// ----------------------------------------------------------------------------
// GMacKey
// ----------------------------------------------------------------------------
bool GMacKey::operator < (const GMacKey& rhs) const
{
  return (mac < rhs.mac);
}

// ----------------------------------------------------------------------------
// GMacFlowKey
// ----------------------------------------------------------------------------
bool GMacFlowKey::operator < (const GMacFlowKey& rhs) const
{
  if (this->srcMac < rhs.srcMac) return true;
  if (this->srcMac > rhs.srcMac) return false;
  if (this->dstMac < rhs.dstMac) return true;
  return false;
}

GMacFlowKey GMacFlowKey::reverse()
{
  GMacFlowKey res;
  res.srcMac = this->dstMac;
  res.dstMac = this->srcMac;
  return res;
}

// ----------------------------------------------------------------------------
// GMacSessionKey
// ----------------------------------------------------------------------------
bool GMacSessionKey::operator < (const GMacSessionKey& rhs) const
{
  if (this->mac1 < rhs.mac1) return true;
  if (this->mac1 > rhs.mac1) return false;
  if (this->mac2 < rhs.mac2) return true;
  return false;
}

// ----------------------------------------------------------------------------
// GIpKey
// ----------------------------------------------------------------------------
bool GIpKey::operator < (const GIpKey& rhs) const
{
  return (this->ip < rhs.ip);
}

// ----------------------------------------------------------------------------
// GIpFlowKey
// ----------------------------------------------------------------------------
bool GIpFlowKey::operator < (const GIpFlowKey& rhs) const
{
  if (this->srcIp < rhs.srcIp) return true;
  if (this->srcIp > rhs.srcIp) return false;
  if (this->dstIp < rhs.dstIp) return true;
  return false;
}

GIpFlowKey GIpFlowKey::reverse()
{
  GIpFlowKey res;
  res.srcIp = this->dstIp;
  res.dstIp = this->srcIp;
  return res;
}

// ----------------------------------------------------------------------------
// GIpSessionKey
// ----------------------------------------------------------------------------
bool GIpSessionKey::operator < (const GIpSessionKey& rhs) const
{
  if (this->ip1 < rhs.ip1) return true;
  if (this->ip1 > rhs.ip1) return false;
  if (this->ip2 < rhs.ip2) return true;
  return false;
}

// ----------------------------------------------------------------------------
// GPortKey
// ----------------------------------------------------------------------------
bool GPortKey::operator < (const GPortKey& rhs) const
{
  return (this->port < rhs.port);
}

// ----------------------------------------------------------------------------
// GPortFlowKey
// ----------------------------------------------------------------------------
bool GPortFlowKey::operator < (const GPortFlowKey& rhs) const
{
  if (this->srcPort < rhs.srcPort) return true;
  if (this->srcPort > rhs.srcPort) return false;
  if (this->dstPort < rhs.dstPort) return true;
  return false;
}

GPortFlowKey GPortFlowKey::reverse()
{
  GPortFlowKey res;
  res.srcPort = this->dstPort;
  res.dstPort = this->srcPort;
  return res;
}

// ----------------------------------------------------------------------------
// GPortSessionKey
// ----------------------------------------------------------------------------
bool GPortSessionKey::operator < (const GPortSessionKey& rhs) const
{
  if (this->port1 < rhs.port1) return true;
  if (this->port1 > rhs.port1) return false;
  if (this->port2 < rhs.port2) return true;
  return false;
}

// ----------------------------------------------------------------------------
// GTransportKey
// ----------------------------------------------------------------------------
bool GTransportKey::operator < (const GTransportKey& rhs) const
{
  if (this->ip   < rhs.ip) return true;
  if (this->ip   > rhs.ip) return false;
  if (this->port < rhs.port) return true;
  return false;
}

// ----------------------------------------------------------------------------
// GTransportFlowKey
// ----------------------------------------------------------------------------
bool GTransportFlowKey::operator < (const GTransportFlowKey& rhs) const
{
  if (this->srcIp   < rhs.srcIp)   return true;
  if (this->srcIp   > rhs.srcIp)   return false;
  if (this->srcPort < rhs.srcPort) return true;
  if (this->srcPort > rhs.srcPort) return false;
  if (this->dstIp   < rhs.dstIp)   return true;
  if (this->dstIp   > rhs.dstIp)   return false;
  if (this->dstPort < rhs.dstPort) return true;
  return false;
}

bool GTransportFlowKey::operator == (const GTransportFlowKey& rhs) const
{
  if (this->srcIp   != rhs.srcIp)   return false;
  if (this->srcIp   != rhs.srcIp)   return false;
  if (this->srcPort != rhs.srcPort) return false;
  if (this->srcPort != rhs.srcPort) return false;
  if (this->dstIp   != rhs.dstIp)   return false;
  if (this->dstIp   != rhs.dstIp)   return false;
  if (this->dstPort != rhs.dstPort) return false;
  return true;
}

GTransportFlowKey GTransportFlowKey::reverse()
{
  GTransportFlowKey res;
  res.srcIp   = this->dstIp;
  res.srcPort = this->dstPort;
  res.dstIp   = this->srcIp;
  res.dstPort = this->srcPort;
  return res;
}

// ----------------------------------------------------------------------------
// GTransportSessionKey
// ----------------------------------------------------------------------------
bool GTransportSessionKey::operator < (const GTransportSessionKey& rhs) const
{
  if (this->ip1   < rhs.ip1)   return true;
  if (this->ip1   > rhs.ip1)   return false;
  if (this->port1 < rhs.port1) return true;
  if (this->port1 > rhs.port1) return false;
  if (this->ip2   < rhs.ip2)   return true;
  if (this->ip2   > rhs.ip2)   return false;
  if (this->port2 < rhs.port2) return true;
  return false;
}

// ----------------------------------------------------------------------------
// GTupleFlowKey
// ----------------------------------------------------------------------------
bool GTupleFlowKey::operator < (const GTupleFlowKey& rhs) const
{
  if (this->proto < rhs.proto) return true;
  if (this->proto > rhs.proto) return false;
  return this->flow < rhs.flow;
}

GTupleFlowKey GTupleFlowKey::reverse()
{
  GTupleFlowKey res;
  res.proto = this->proto;
  res.flow  = this->flow.reverse();
  return res;
}
