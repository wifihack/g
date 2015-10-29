#include "gpackethdr.h"

// ----------------------------------------------------------------------------
// GEthHdr
// ----------------------------------------------------------------------------
bool GEthHdr::is(uint16_t etherType, void** networkHdr) {
  if (ntohs(this->ether_type) != etherType)
    return false;
  if (networkHdr != nullptr)
    *networkHdr = (void*)((uint8_t*)this + sizeof(GEthHdr));
  return true;
}

bool GEthHdr::isIp(GIpHdr** ipHdr) {
  return is(ETHERTYPE_IP, (void**)ipHdr);
}

bool GEthHdr::isArp(GArpHdr** arpHdr) {
  return is(ETHERTYPE_ARP, (void**)arpHdr);
}

// ----------------------------------------------------------------------------
// GIpHdr
// ----------------------------------------------------------------------------
bool GIpHdr::is(uint8_t protocol, void** transportHdr) {
  if (this->ip_p != protocol)
    return false;
  if (transportHdr != NULL)
    *transportHdr = (void*)((uint8_t*)(this) + this->ip_hl * sizeof(uint32_t));
  return true;
}

bool GIpHdr::isTcp(GTcpHdr** tcpHdr) {
  return is(IPPROTO_TCP, (void**)tcpHdr);
}

bool GIpHdr::isUdp(GUdpHdr** udpHdr) {
  return is(IPPROTO_UDP, (void**)udpHdr);
}

bool GIpHdr::isIcmp(GIcmpHdr** icmpHdr) {
  return is(IPPROTO_ICMP, (void**)icmpHdr);
}

//
// All ipHdr field except ipHdr.ip_sum
//
uint16_t GIpHdr::checksum() {
  int i;
  uint32_t sum;
  uint16_t *p;

  sum = 0;

  // Add ipHdr buffer as array of uint16_t
  p = (uint16_t*)this;
  for (i = 0; i < (int)sizeof(GIpHdr) / 2; i++)
  {
    sum += ntohs(*p);
    p++;
  }

  // Do not consider padding because ip header length is always multilpe of 2.

  // Decrease checksum from sum
  sum -= ntohs(this->ip_sum);

  // Recalculate sum
  while(sum >> 16)
  {
    sum = (sum & 0xFFFF) + (sum >> 16);
  }
  sum = ~sum;

  return (uint16_t)sum;
}

uint16_t GIpHdr::recalculateChecksum(uint16_t oldChecksum, uint16_t oldValue, uint16_t newValue) {
  uint32_t sum;

  sum = oldValue + (~newValue & 0xFFFF);
  sum += oldChecksum;
  sum = (sum & 0xFFFF) + (sum >> 16);
  return (uint16_t)(sum + (sum >> 16));
}

uint16_t GIpHdr::recalculateChecksum(uint16_t oldChecksum, uint32_t oldValue, uint32_t newValue) {
  uint16_t oldValue16;
  uint16_t newValue16;
  uint16_t sum;

  oldValue16 = (oldValue & 0xFFFF0000) >> 16;
  newValue16 = (newValue & 0xFFFF0000) >> 16;
  sum        = recalculateChecksum(oldChecksum, oldValue16, newValue16);

  oldValue16 = oldValue & 0x0000ffff;
  newValue16 = newValue & 0x0000ffff;
  sum        = recalculateChecksum(sum, oldValue16, newValue16);

  return sum;
}

// ----------------------------------------------------------------------------
// GTcpHdr
// ----------------------------------------------------------------------------
bool GTcpHdr::isData(GIpHdr* ipHdr, uint8_t** tcpData, int* tcpDataLen) {
  int   tcpHdrLen   = this->th_off * sizeof(uint32_t);
  uint8_t* _tcpData    = (uint8_t*)this + tcpHdrLen;
  int   _tcpDataLen = ntohs(ipHdr->ip_len) - sizeof(GIpHdr) - tcpHdrLen;

  if (_tcpDataLen > 0)
  {
    if (tcpData != nullptr)
      *tcpData = _tcpData;
    if (tcpDataLen != nullptr)
      *tcpDataLen = _tcpDataLen;
    return true;
  }
  return false;
}

bool GTcpHdr::isOption(uint8_t** tcpOption, int* tcpOptionLen) {
  int tcpHdrLen = this->th_off * sizeof(uint32_t);
  int _tcpOptionLen = tcpHdrLen - sizeof(GTcpHdr);
  if (tcpOption != NULL)
    *tcpOption = (uint8_t*)this + sizeof(GTcpHdr);
  if (tcpOptionLen != NULL)
    *tcpOptionLen = _tcpOptionLen;
  return _tcpOptionLen > 0;
}

//
// All tcpHdr field except tcpHdr.th_sum
// All data buffer(padding)
// ipHdr.ip_src, ipHdr.ip_dst, tcpHdrDataLen and IPPROTO_TCP
//
uint16_t GTcpHdr::checksum(GIpHdr* ipHdr) {
  int i;
  int tcpHdrDataLen;
  uint32_t src, dst;
  uint32_t sum;
  uint16_t *p;

  tcpHdrDataLen = ntohs(ipHdr->ip_len) - sizeof(GIpHdr);
  sum = 0;

  // Add tcpHdr and data buffer as array of UIN16
  p = (uint16_t*)this;
  for (i = 0; i < tcpHdrDataLen / 2; i++)
  {
    sum += htons(*p);
    p++;
  }

  // If length is odd, add last data(padding)
  if ((tcpHdrDataLen / 2) * 2 != tcpHdrDataLen)
    sum += (htons(*p) & 0xFF00);

  // Decrease checksum from sum
  sum -= ntohs(this->th_sum);

  // Add src address
  src = ntohl(ipHdr->ip_src);
  sum += ((src & 0xFFFF0000) >> 16) + (src & 0x0000FFFF);

  // Add dst address
  dst = ntohl(ipHdr->ip_dst);
  sum += ((dst & 0xFFFF0000) >> 16) + (dst & 0x0000FFFF);

  // Add extra information
  sum += (uint32_t)(tcpHdrDataLen) + IPPROTO_TCP;

  // Recalculate sum
  while(sum >> 16)
  {
    sum = (sum & 0xFFFF) + (sum >> 16);
  }
  sum = ~sum;

  return (uint16_t)sum;
}

int GTcpHdr::getOption(
  uint8_t*    tcpOption,
  int         tcpOptionLen,
  GTcpOption& _tcpOption) {
  uint8_t*      p;
  uint8_t       kind;
  uint8_t       len;

  p = (uint8_t*)tcpOption;

  //
  // Set kind
  //
  if (tcpOptionLen < 1) return 0;
  kind = *p; p++; tcpOptionLen--;
  _tcpOption.kind = kind;

  //
  // Set Length and Value
  //
  if (kind != 0 && kind != 1)
  {
    if (tcpOptionLen < 1) return 0;
    len = *p; p++; tcpOptionLen--;
    _tcpOption.len = len;

    if (tcpOptionLen < len - 2) return 0;
    _tcpOption.value = (uint8_t*)p;
    p += len - 2; // p++; tcpOptionLen--; // remove warning
  }

  //
  // Set desc
  //
  const char* desc;
  switch (kind)
  {
    case  0:  desc = "EOL";                                 break;
    case  1:  desc = "NOP";                                 break;
    case  2:  desc = "MSS";                                 break;
    case  3:  desc = "Window Scale";                        break;
    case  4:  desc = "SACK Permitted";                      break;
    case  5:  desc = "SACK";                                break;
    case  6:  desc = "Echo (obsoleted by option 8)";        break;
    case  7:  desc = "Echo Reply (obsoleted by option 8";   break;
    case  8:  desc = "TSOPT - Time Stamp Option";           break;
    case  9:  desc = "Partial Order Connection Permitte";   break;
    case  10: desc = "Partial Order Service Profile";       break;
    case  11: desc = "CC";                                  break;
    case  12: desc = "CC.NEW";                              break;
    case  13: desc = "CC.ECHO";                             break;
    case  14: desc = "TCP Alternate Checksum Request";      break;
    case  15: desc = "TCP Alternate Checksum Data";         break;
    case  16: desc = "Skeeter";                             break;
    case  17: desc = "Bubba";                               break;
    case  18: desc = "Trailer Checksum Option";             break;
    case  19: desc = "MD5 Signature Option";                break;
    case  20: desc = "SCPS Capabilities";                   break;
    case  21: desc = "Selective Negative Acknowledgements"; break;
    case  22: desc = "Record Boundaries";                   break;
    case  23: desc = "Corruption experienced";              break;
    case  24: desc = "SNAP";                                break;
    case  25: desc = "Unassigned (released 12/18/00)";      break;
    case  26: desc = "TCP Compression Filter";              break;
    case  27: desc = "Quick-Start Response";                break;
    case 253: desc = "RFC3692-style Experiment 1";          break;
    case 254: desc = "RFC3692-style Experiment 2";          break;
    default : desc = "UNKNOWN";                             break;
  }

  _tcpOption.desc = (uint8_t*)desc;

  return (int)(p - (uint8_t*)tcpOption);
}

int GTcpHdr::getOptionList(
  uint8_t*        tcpOption,
  int             tcpOptionLen,
  GTcpOptionList& tcpOptionList) {
  int totalRes = 0;
  while (true)
  {
    GTcpOption _tcpOption;
    int res = getOption(tcpOption, tcpOptionLen, _tcpOption);
    if (res == 0)
    {
      break;
    }
    tcpOptionList.push_back(_tcpOption);
    tcpOption    += res;
    tcpOptionLen -= res;
    totalRes     += res;
  }
  return totalRes;
}

// ----------------------------------------------------------------------------
// GUdpHdr
// ----------------------------------------------------------------------------
bool GUdpHdr::isData(uint8_t** udpData, int* udpDataLen) {
  int _udpDataLen;

  if (udpData != nullptr)
    *udpData = (uint8_t*)this + sizeof(GUdpHdr);
  _udpDataLen = ntohs(this->uh_ulen) - sizeof(GUdpHdr);
  if (udpDataLen != nullptr)
    *udpDataLen = _udpDataLen;
  return _udpDataLen > 0;
}

//
// All udpHdr field except udpHdr.uh_sum
// All data buffer(padding)
// ipHdr.ip_src, ipHdr.ip_dst, udpHdrDataLen and IPPROTO_UDP
//
uint16_t GUdpHdr::checksum(GIpHdr* ipHdr) {
  int i;
  int udpHdrDataLen;
  uint16_t *p;
  uint32_t src, dst;
  uint32_t sum;

  udpHdrDataLen = ntohs(this->uh_ulen);
  sum = 0;

  // Add udpHdr & data buffer as array of uint16_t
  p = (uint16_t*)this;
  for (i = 0; i < udpHdrDataLen / 2; i++)
  {
    sum += htons(*p);
    p++;
  }

  // If length is odd, add last data(padding)
  if ((udpHdrDataLen / 2) * 2 != udpHdrDataLen)
    sum += (htons(*p) & 0xFF00);

  // Decrease checksum from sum
  sum -= ntohs(this->uh_sum);

  // Add src address
  src = ntohl(ipHdr->ip_src);
  sum += ((src & 0xFFFF0000) >> 16) + (src & 0x0000FFFF);

  // Add dst address
  dst = ntohl(ipHdr->ip_dst);
  sum += ((dst & 0xFFFF0000) >> 16) + (dst & 0x0000FFFF);

  // Add extra information
  sum += (uint32_t)udpHdrDataLen + IPPROTO_UDP;

  // Recalculate sum
  while ((sum >> 16) > 0)
  {
    sum = (sum & 0xFFFF) + (sum >> 16);
  }
  sum = ~sum;

  return (uint16_t)sum;
}

// ----------------------------------------------------------------------------
// GIcmpHdr
// ----------------------------------------------------------------------------
bool GIcmpHdr::isData(GIpHdr* ipHdr, uint8_t** icmpData, int* icmpDataLen) {
  (void)ipHdr;
  (void)icmpData;
  (void)icmpDataLen;
  return false; // gilgil temp 2009.09.08
}

//
// All icmpHdr field except icmpHdr.uh_sum
// Added ipHdr.ip_src, ipHdr.ip_dst, icmpHdrDataLen and IPPROTO_ICMP
//
uint16_t GIcmpHdr::checksum(GIpHdr* ipHdr) {
  (void)ipHdr;
  return 0;

  /* gilgil temp 2009.09.08
  int i;
  int icmpHdrDataLen;
  uint16_t *p;
  uint32_t src, dst;
  uint32_t sum;

  icmpHdrDataLen = ntohs(icmpHdr->uh_ulen);
  sum = 0;

  // Add icmpHdr & data buffer as array of uint16_t
  p = (uint16_t*)icmpHdr;
  for (i = 0; i < icmpHdrDataLen / 2; i++)
  {
    sum += htons(*p);
    p++;
  }

  // If length is odd, add Last Data
  if ((icmpHdrDataLen / 2) * 2 != icmpHdrDataLen)
    sum += (htons(*p) & 0xFF00);

  // Decrease checksum from sum
  sum -= ntohs(icmpHdr->uh_sum);

  // Add src address
  src = ntohl(ipHdr->ip_src);
  sum += ((src & 0xFFFF0000) >> 16) + (src & 0x0000FFFF);

  // Add dst address
  dst = ntohl(ipHdr->ip_dst);
  sum += ((dst & 0xFFFF0000) >> 16) + (dst & 0x0000FFFF);

  // Add extra onformation
  sum += (uint32_t)icmpHdrDataLen + IPPROTO_ICMP;

  // Recalculate sum
  while ((sum >> 16) > 0)
    sum = (sum & 0xFFFF) + (sum >> 16);
  sum = ~sum;

  return (uint16_t)sum;
  */
}

// ----- gilgil temp 2015.10.29 -----
/*
// ----------------------------------------------------------------------------
// GDnsQuestion
// ----------------------------------------------------------------------------
QByteArray encode()
bool       decode(uint8_t* udpData, int dataLen, int* offset)

// ----------------------------------------------------------------------------
// GDnsQuestions
// ----------------------------------------------------------------------------
QByteArray encode()
bool       decode(uint8_t* udpData, int dataLen, int count, int* offset)

// ----------------------------------------------------------------------------
// GDnsResourceRecord
// ----------------------------------------------------------------------------
QByteArray encode()
bool       decode(uint8_t* udpData, int dataLen, int* offset)

// ----------------------------------------------------------------------------
// GDnsResourceRecords
// ----------------------------------------------------------------------------
QByteArray encode()
bool       decode(uint8_t* udpData, int dataLen, int count, int* offset)

// ----------------------------------------------------------------------------
// GDns
// ----------------------------------------------------------------------------
QByteArray encode()
bool       decode(uint8_t* udpData, int dataLen, int* offset)
static QByteArray encodeName(QString name)
static QString    decodeName(uint8_t* udpData, int dataLen, int* offset)
*/
// ----------------------------------
