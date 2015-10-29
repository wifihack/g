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

#include <netinet/in.h>
#include <pcap.h>

#pragma pack(push, 1)
#include "net/libnet/config.h"
#include "net/libnet/libnet-macros.h"
#include "net/libnet/libnet-headers.h"
#pragma pack(pop)

#include <QList>
#include "net/gmac.h"
#include "net/gip.h"

// ----------------------------------------------------------------------------
// Link Layer Type
// ----------------------------------------------------------------------------
#ifndef DLT_NULL
#define DLT_NULL                       0
#endif
#ifndef DLT_EN10MB
#define DLT_EN10MB                     1
#endif
#ifndef DLT_AX25
#define DLT_AX25                       3
#endif
#ifndef DLT_IEEE802
#define DLT_IEEE802                    6
#endif
#ifndef DLT_ARCNET
#define DLT_ARCNET                     7
#endif
#ifndef DLT_SLIP
#define DLT_SLIP                       8
#endif
#ifndef DLT_PPP
#define DLT_PPP                        9
#endif
#ifndef DLT_FDDI
#define DLT_FDDI                       10
#endif
#ifndef DLT_PPP_SERIAL
#define DLT_PPP_SERIAL                 50
#endif
#ifndef DLT_PPP_ETHER
#define DLT_PPP_ETHER                  51
#endif
#ifndef DLT_ATM_RFC1483
#define DLT_ATM_RFC1483                100
#endif
#ifndef DLT_RAW
#define DLT_RAW                        101
#endif
#ifndef DLT_C_HDLC
#define DLT_C_HDLC                     104
#endif
#ifndef DLT_IEEE802_11
#define DLT_IEEE802_11                 105
#endif
#ifndef DLT_FRELAY
#define DLT_FRELAY                     107
#endif
#ifndef DLT_LOOP
#define DLT_LOOP                       108
#endif
#ifndef DLT_LINUX_SLL
#define DLT_LINUX_SLL                  113
#endif
#ifndef DLT_LTALK
#define DLT_LTALK                      114
#endif
#ifndef DLT_PFLOG
#define DLT_PFLOG                      117
#endif
#ifndef DLT_PRISM_HEADER
#define DLT_PRISM_HEADER               119
#endif
#ifndef DLT_IP_OVER_FC
#define DLT_IP_OVER_FC                 122
#endif
#ifndef DLT_SUNATM
#define DLT_SUNATM                     123
#endif
#ifndef DLT_IEEE802_11_RADIO
#define DLT_IEEE802_11_RADIO           127
#endif
#ifndef DLT_ARCNET_LINUX
#define DLT_ARCNET_LINUX               129
#endif
#ifndef DLT_APPLE_IP_OVER_IEEE1394
#define DLT_APPLE_IP_OVER_IEEE1394     138
#endif
#ifndef DLT_MTP2_WITH_PHDR
#define DLT_MTP2_WITH_PHDR             139
#endif
#ifndef DLT_MTP2
#define DLT_MTP2                       140
#endif
#ifndef DLT_MTP3
#define DLT_MTP3                       141
#endif
#ifndef DLT_SCCP
#define DLT_SCCP                       142
#endif
#ifndef DLT_DOCSIS
#define DLT_DOCSIS                     143
#endif
#ifndef DLT_LINUX_IRDA
#define DLT_LINUX_IRDA                 144
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER0
#define LINKTYPE_USER0_LINKTYPE_USER0  147
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER1
#define LINKTYPE_USER0_LINKTYPE_USER1  148
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER2
#define LINKTYPE_USER0_LINKTYPE_USER2  149
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER3
#define LINKTYPE_USER0_LINKTYPE_USER3  150
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER4
#define LINKTYPE_USER0_LINKTYPE_USER4  151
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER5
#define LINKTYPE_USER0_LINKTYPE_USER5  152
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER6
#define LINKTYPE_USER0_LINKTYPE_USER6  153
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER7
#define LINKTYPE_USER0_LINKTYPE_USER7  154
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER8
#define LINKTYPE_USER0_LINKTYPE_USER8  155
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER9
#define LINKTYPE_USER0_LINKTYPE_USER9  156
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER10
#define LINKTYPE_USER0_LINKTYPE_USER10 157
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER11
#define LINKTYPE_USER0_LINKTYPE_USER11 158
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER12
#define LINKTYPE_USER0_LINKTYPE_USER12 159
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER13
#define LINKTYPE_USER0_LINKTYPE_USER13 160
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER14
#define LINKTYPE_USER0_LINKTYPE_USER14 161
#endif
#ifndef LINKTYPE_USER0_LINKTYPE_USER15
#define LINKTYPE_USER0_LINKTYPE_USER15 162
#endif
#ifndef DLT_IEEE802_11_RADIO_AVS
#define DLT_IEEE802_11_RADIO_AVS       163
#endif
#ifndef DLT_BACNET_MS_TP
#define DLT_BACNET_MS_TP               165
#endif
#ifndef DLT_PPP_PPPD
#define DLT_PPP_PPPD                   166
#endif
#ifndef DLT_GPRS_LLC
#define DLT_GPRS_LLC                   169
#endif
#ifndef DLT_LINUX_LAPD
#define DLT_LINUX_LAPD                 177
#endif
#ifndef DLT_BLUETOOTH_HCI_H4
#define DLT_BLUETOOTH_HCI_H4           187
#endif
#ifndef DLT_USB_LINUX
#define DLT_USB_LINUX                  189
#endif
#ifndef DLT_PPI
#define DLT_PPI                        192
#endif
#ifndef DLT_IEEE802_15_4
#define DLT_IEEE802_15_4               195
#endif
#ifndef DLT_SITA
#define DLT_SITA                       196
#endif
#ifndef DLT_ERF
#define DLT_ERF                        197
#endif
#ifndef DLT_BLUETOOTH_HCI_H4_WITH_PHDR
#define DLT_BLUETOOTH_HCI_H4_WITH_PHDR 201
#endif
#ifndef DLT_AX25_KISS
#define DLT_AX25_KISS                  202
#endif
#ifndef DLT_LAPD
#define DLT_LAPD                       203
#endif
#ifndef DLT_PPP_WITH_DIR
#define DLT_PPP_WITH_DIR               204
#endif
#ifndef DLT_C_HDLC_WITH_DIR
#define DLT_C_HDLC_WITH_DIR            205
#endif
#ifndef DLT_FRELAY_WITH_DIR
#define DLT_FRELAY_WITH_DIR            206
#endif
#ifndef DLT_IPMB_LINUX
#define DLT_IPMB_LINUX                 209
#endif
#ifndef DLT_IEEE802_15_4_NONASK_PHY
#define DLT_IEEE802_15_4_NONASK_PHY    215
#endif
#ifndef DLT_USB_LINUX_MMAPPED
#define DLT_USB_LINUX_MMAPPED          220
#endif
#ifndef DLT_FC_2
#define DLT_FC_2                       224
#endif
#ifndef DLT_FC_2_WITH_FRAME_DELIMS
#define DLT_FC_2_WITH_FRAME_DELIMS     225
#endif
#ifndef DLT_IPNET
#define DLT_IPNET                      226
#endif
#ifndef DLT_CAN_SOCKETCAN
#define DLT_CAN_SOCKETCAN              227
#endif
#ifndef DLT_IPV4
#define DLT_IPV4                       228
#endif
#ifndef DLT_IPV6
#define DLT_IPV6                       229
#endif
#ifndef DLT_IEEE802_15_4_NOFCS
#define DLT_IEEE802_15_4_NOFCS         230
#endif
#ifndef DLT_DBUS
#define DLT_DBUS                       231
#endif
#ifndef DLT_DVB_CI
#define DLT_DVB_CI                     235
#endif
#ifndef DLT_MUX27010
#define DLT_MUX27010                   236
#endif
#ifndef DLT_STANAG_5066_D_PDU
#define DLT_STANAG_5066_D_PDU          237
#endif
#ifndef DLT_NFLOG
#define DLT_NFLOG                      239
#endif
#ifndef DLT_NETANALYZER
#define DLT_NETANALYZER                240
#endif
#ifndef DLT_NETANALYZER_TRANSPARENT
#define DLT_NETANALYZER_TRANSPARENT    241
#endif
#ifndef DLT_IPOIB
#define DLT_IPOIB                      242
#endif
#ifndef DLT_MPEG_2_TS
#define DLT_MPEG_2_TS                  243
#endif
#ifndef DLT_NG40
#define DLT_NG40                       244
#endif
#ifndef DLT_NFC_LLCP
#define DLT_NFC_LLCP                   245
#endif

// ----------------------------------------------------------------------------
// GPktHdr
// ----------------------------------------------------------------------------
typedef struct pcap_pkthdr             GPktHdr;

#pragma pack(push, 1)

// ----------------------------------------------------------------------------
// GEthHdr
// ----------------------------------------------------------------------------
struct GIpHdr;
struct GArpHdr;
struct GEthHdr { // libnet_ethernet_hdr
  GMac ether_dhost;     /* destination ethernet address */
  GMac ether_shost;     /* source ethernet address */
  u_int16_t ether_type; /* protocol */

public:
  bool is   (uint16_t etherType, void** networkHdr);
  bool isIp (GIpHdr** ipHdr);
  bool isArp(GArpHdr** arpHdr);
};

// ----------------------------------------------------------------------------
// GFddiHdr
// ----------------------------------------------------------------------------
typedef struct libnet_fddi_hdr GFddiHdr;

// ----------------------------------------------------------------------------
// GIpHdr
// ----------------------------------------------------------------------------
struct GTcpHdr;
struct GUdpHdr;
struct GIcmpHdr;
struct GIpHdr { // libnet_ipv4_hdr
#if (LIBNET_LIL_ENDIAN)
  u_int8_t  ip_hl:4,        /* header length */
            ip_v:4;         /* version */
#endif
#if (LIBNET_BIG_ENDIAN)
  u_int8_t  ip_v:4,         /* version */
            ip_hl:4;        /* header length */
#endif
  u_int8_t  ip_tos;         /* type of service */
  u_int16_t ip_len;         /* total length */
  u_int16_t ip_id;          /* identification */
  u_int16_t ip_off;
  u_int8_t  ip_ttl;         /* time to live */
  u_int8_t  ip_p;           /* protocol */
  u_int16_t ip_sum;         /* checksum */
  GIp       ip_src, ip_dst; /* source and dest address */

public:
  bool is    (uint8_t protocol, void** transportHdr);
  bool isTcp (GTcpHdr**  tcpHdr);
  bool isUdp (GUdpHdr**  udpHdr);
  bool isIcmp(GIcmpHdr** icmpHdr);
  uint16_t checksum();
  static uint16_t recalculateChecksum(uint16_t oldChecksum, uint16_t oldValue, uint16_t newValue);
  static uint16_t recalculateChecksum(uint16_t oldChecksum, uint32_t oldValue, uint32_t newValue);
};

// ----------------------------------------------------------------------------
// GArpHdr
// ----------------------------------------------------------------------------
struct GArpHdr : libnet_arp_hdr {
  GMac ar_sa;
  GIp  ar_si;
  GMac ar_ta;
  GIp  ar_ti;
};

// ----------------------------------------------------------------------------
// GTcpOption
// ----------------------------------------------------------------------------
struct GTcpOption
{
  uint8_t kind;
  uint8_t len;
  uint8_t* value;
  uint8_t* desc;
};
typedef QList<GTcpOption> GTcpOptionList;

// ----------------------------------------------------------------------------
/* from : http://www.iana.org/assignments/tcp-parameters

TCP OPTION NUMBERS

(last updated 2007-02-15)

The Transmission Control Protocol (TCP) has provision for optional
header fields identified by an option kind field.  Options 0 and 1 are
exactly one octet which is their kind field.  All other options have
their one octet kind field, followed by a one octet length field,
followed by length-2 octets of option data.

Kind   Length   Meaning                           Reference
----   ------   -------------------------------   ---------
  0        -    End of Option List                 [RFC793]
  1        -    No-Operation                       [RFC793]
  2        4    Maximum Segment Size               [RFC793]
  3        3    WSOPT - Window Scale              [RFC1323]
  4        2    SACK Permitted                    [RFC2018]
  5        N    SACK                              [RFC2018]
  6        6    Echo (obsoleted by option 8)      [RFC1072]
  7        6    Echo Reply (obsoleted by option 8)[RFC1072]
  8       10    TSOPT - Time Stamp Option         [RFC1323]
  9        2    Partial Order Connection Permitted[RFC1693]
   10        3    Partial Order Service Profile     [RFC1693]
   11             CC                                [RFC1644]
   12             CC.NEW                            [RFC1644]
   13             CC.ECHO                           [RFC1644]
   14         3   TCP Alternate Checksum Request    [RFC1146]
   15         N   TCP Alternate Checksum Data       [RFC1146]
   16             Skeeter                           [Knowles]
   17             Bubba                             [Knowles]
   18         3   Trailer Checksum Option    [Subbu & Monroe]
   19        18   MD5 Signature Option              [RFC2385]
   20             SCPS Capabilities                   [Scott]
   21             Selective Negative Acknowledgements [Scott]
   22             Record Boundaries                   [Scott]
   23             Corruption experienced              [Scott]
   24             SNAP         [Sukonnik]
   25             Unassigned (released 12/18/00)
   26             TCP Compression Filter           [Bellovin]
   27          8  Quick-Start Response              [RFC4782]
   28-252         Unassigned
   253         N  RFC3692-style Experiment 1 (*)    [RFC4727]
   254         N  RFC3692-style Experiment 2 (*)    [RFC4727]

(*) It is only appropriate to use these values in explicitly-
    configured experiments; they MUST NOT be shipped as defaults in
    implementations.  See RFC 3692 for details.


TCP ALTERNATE CHECKSUM NUMBERS

Number  Description      Reference
------- ------------------------------- ----------
   0    TCP Checksum                    [RFC-1146]
   1    8-bit Fletchers's algorithm     [RFC-1146]
   2    16-bit Fletchers's algorithm    [RFC-1146]
   3    Redundant Checksum Avoidance    [Kay]

*/
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// GTcpHdr
// ----------------------------------------------------------------------------
struct GTcpHdr : libnet_tcp_hdr {
  bool isData(GIpHdr* ipHdr, uint8_t** tcpData = nullptr, int* tcpDataLen = nullptr);
  bool isOption(uint8_t** tcpOption = nullptr, int* tcpOptionLen = nullptr);
  uint16_t checksum(GIpHdr* ipHdr);

  static int getOption( // Return one GTcpOption buffer size
    uint8_t*    tcpOption,
    int         tcpOptionLen,
    GTcpOption& _tcpOption);

  static int getOptionList( // Return total snoopTCPOption buffer size
    uint8_t*        tcpOption,
    int             tcpOptionLen,
    GTcpOptionList& tcpOptionList);
};

// ----------------------------------------------------------------------------
// GUdpHdr
// ----------------------------------------------------------------------------
struct GUdpHdr : libnet_udp_hdr {
  bool isData(uint8_t** udpData = nullptr, int* udpDataLen = nullptr);
  uint16_t checksum(GIpHdr* ipHdr);
};

// ----------------------------------------------------------------------------
// GIcmpHdr
// ----------------------------------------------------------------------------
struct GIcmpHdr : libnet_icmpv4_hdr {
public:
  bool isData(GIpHdr* ipHdr, uint8_t** icmpData = nullptr, int* icmpDataLen = nullptr);
  uint16_t checksum(GIpHdr* ipHdr);
};

// ----------------------------------------------------------------------------
// GDnsHdr
// ----------------------------------------------------------------------------
struct GDnsHdr {
  u_int16_t id;             /* DNS packet ID */
  u_int16_t flags;          /* DNS flags */
  u_int16_t num_q;          /* Number of questions */
  u_int16_t num_answ_rr;    /* Number of answer resource records */
  u_int16_t num_auth_rr;    /* Number of authority resource records */
  u_int16_t num_addi_rr;    /* Number of additional resource records */
};

// ----------------------------------------------------------------------------
// GDnsQuestion
// ----------------------------------------------------------------------------
struct GDnsQuestion {
  QString  name;
  uint16_t type;
  uint16_t _class;

public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int* offset);
};

// ----------------------------------------------------------------------------
// GDnsQuestions
// ----------------------------------------------------------------------------
struct GDnsQuestions : QList<int> {
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int count, int* offset);
};

// ----------------------------------------------------------------------------
// GDnsResourceRecord
// ----------------------------------------------------------------------------
struct GDnsResourceRecord {
  QString  name;
  uint16_t type;
  uint16_t _class;
  uint32_t ttl;
  uint16_t dataLength;
  QByteArray data;

public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int* offset);
};

// ----------------------------------------------------------------------------
// GDnsResourceRecords
// ----------------------------------------------------------------------------
struct GDnsResourceRecords : QList<GDnsResourceRecord> {
public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int count, int* offset);
};

// ----------------------------------------------------------------------------
// GDns
// ----------------------------------------------------------------------------
struct GDnsInfo {
public:
  GDnsHdr dnsHdr;
  GDnsQuestions questions;
  GDnsResourceRecords answers;
  GDnsResourceRecords authorities;
  GDnsResourceRecords additionals;

public:
  QByteArray encode();
  bool       decode(uint8_t* udpData, int dataLen, int* offset);

public:
  static QByteArray encodeName(QString name);
  static QString    decodeName(uint8_t* udpData, int dataLen, int* offset);
};

#pragma pack(pop)
