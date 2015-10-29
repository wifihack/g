#include "gpcap.h"

// ----------------------------------------------------------------------------
// GPcap
// ----------------------------------------------------------------------------
GPcap::~GPcap() {
  close();
}

bool GPcap::doOpen() {
  if (pcap_ != nullptr) {
    SET_ERR(GStdErr(GErr::VALUE_IS_NOT_NULL, "pcap is not null"));
    return false;
  }

  char errBuf[PCAP_ERRBUF_SIZE];
  pcap_ = pcap_open_live(qPrintable(dev_), snapLen_, flags_, readTimeout_, errBuf);
  if (pcap_ == nullptr) {
    SET_ERR(GStdErr(GErr::RETURN_NULL, errBuf));
    return false;
  }

  bool filtering = false;
  int dataLink = pcap_datalink(pcap_);
  switch (dataLink) {
    case DLT_NULL:
    case DLT_EN10MB:
      filtering = true;
  }
  if (filtering && filter_ != "") {
    if (!pcapProcessFilter(nullptr)) // gilgil temp 2015.10.28
      return false;
  }

  return GCapture::doOpen();
}

bool GPcap::doClose() {
  // ----- by gilgil 2009.09.01 -----
  // Strange to say, when pcap_next_ex is called after pcap_close is called, it occurs memory problem.
  // So waits until thread is terminated.

  bool res = GCapture::doClose();

  if (pcap_ != nullptr) {
    pcap_close(pcap_);
    pcap_ = nullptr;
  }
  // --------------------------------

  return res;
}

GCapture::Result GPcap::read(GPacket* packet) {
  int i = pcap_next_ex(pcap_, &(packet->pktHdr), (const u_char **)&(packet->pktData));
  Result res;
  switch (i) {
    case -2: // if EOF was reached reading from an offline capture
      SET_ERR(GStdErr(ERROR_IN_PCAP_NEXT_EX, QString("pcap_next_ex return -2(%1)").arg(pcap_geterr(pcap_))));
      res = Eof;
      break;
    case -1: // if an error occurred
      SET_ERR(GStdErr(ERROR_IN_PCAP_NEXT_EX, QString("pcap_next_ex return -1(%1)").arg(pcap_geterr(pcap_))));
      res = Fail;
      break;
    case 0 : // if a timeout occured
      res = TimeOut;
      break;
    default: // packet captured
      packet->capture = this;
      // if (autoParse_) parse(packet); // gilgil temp 2015.10.29
      res = Ok;
      break;
  }
  return res;
}

GCapture::Result GPcap::write(GPacket* packet) {
  int i = pcap_sendpacket(pcap_, (const u_char*)packet->pktData, (int)packet->pktHdr->caplen);
  if (i == 0) return Ok;
  qWarning() << QString("pcap_sendpacket return %1").arg(i);
  return Fail;
}

GCapture::Result GPcap::relay(GPacket* packet) {
  (void)packet;
  SET_ERR(GStdErr(GErr::NOT_SUPPORTED, "not supported"));
  return Fail;
}

#include <netinet/in.h>
bool GPcap::pcapProcessFilter(pcap_if_t* dev) {
  u_int uNetMask;
  bpf_program code;

  if (dev != NULL && dev->addresses != NULL && dev->addresses->netmask != NULL)
    uNetMask = ((struct sockaddr_in*)(dev->addresses->netmask))->sin_addr.s_addr;
  else
    uNetMask = 0xFFFFFFFF;
  if (pcap_compile(pcap_, &code, qPrintable(filter_), 1, uNetMask) < 0)
  {
    SET_ERR(GStdErr(GErr::UNKNOWN, QString("error in pcap_compile(%1)").arg(pcap_geterr(pcap_))));
    return false;
  }
  if (pcap_setfilter(pcap_, &code) < 0)
  {
    SET_ERR(GStdErr(GErr::UNKNOWN, QString("error in pcap_setfilter(%1)").arg(pcap_geterr(pcap_))));
    return false;
  }
  return true;
}

