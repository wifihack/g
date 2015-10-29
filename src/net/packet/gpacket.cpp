#include "gpacket.h"

// ----------------------------------------------------------------------------
// GPacket
// ----------------------------------------------------------------------------
void GPacket::parse() {
  ethHdr = (GEthHdr*)pktData; // eth
  if (ethHdr->isIp(&ipHdr)) { // ip
    netType = ETHERTYPE_IP;
    if (ipHdr->isTcp(&tcpHdr)) { // tcp
      proto = IPPROTO_TCP;
      tcpHdr->isData(ipHdr, &data, &dataLen); // tcp data
    } else
    if (ipHdr->isUdp(&udpHdr)) { // udp
      proto = IPPROTO_UDP;
      udpHdr->isData(&data, &dataLen); // udp data
    } else
    if (ipHdr->isIcmp(&icmpHdr)) { // icmp
      proto = IPPROTO_ICMP;
      icmpHdr->isData(ipHdr, &data, &dataLen); // icmp data
    }
  } else
  if (ethHdr->isArp(&arpHdr)) { // arp
    netType = ETHERTYPE_ARP;
  }
}

void GPacket::clear() {
  memset(this, 0, sizeof(*this));
}
