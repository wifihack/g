#include "gcapture.h"

// ----------------------------------------------------------------------------
// GCaptureThread
// ----------------------------------------------------------------------------
void GCaptureThread::run() {
  GCapture* capture = dynamic_cast<GCapture*>(parent());
  Q_ASSERT(capture != nullptr);
  capture->run();
}

// ----------------------------------------------------------------------------
// GCapture
// ----------------------------------------------------------------------------
GCapture::~GCapture() {
  close();
}

bool GCapture::doOpen() {
  if (autoRead_)
  {
    // ----- by gilgil 2009.08.31 -----
    //
    // There can be a case that even if thread starts,
    // state remains not not Opened(still Opening) state.
    // So set state_ into Opened before open thread.
    //
    state_ = Opened;
    thread_.start();
    // --------------------------------
  }
  return true;
}

bool GCapture::doClose() {
  if (autoRead_) {
    thread_.quit();
    if (!thread_.wait(G_TIMEOUT)) {
      qCritical() << QString("thread_.wait return false(%1)").arg(this->metaObject()->className());
      return false;
    }
  }
  return true;
}

GCapture::Result GCapture::read(GPacket* packet) {
  (void)packet;
  SET_ERR(GStdErr(GErr::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return Fail;
}

GCapture::Result GCapture::write(GPacket* packet) {
  (void)packet;
  SET_ERR(GStdErr(GErr::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return Fail;
}

GCapture::Result GCapture::relay(GPacket* packet) {
  (void)packet;
  SET_ERR(GStdErr(GErr::VIRTUAL_FUNCTION_CALL, "virtual function call"));
  return Fail;
}

void GCapture::run() {
  qDebug() << "stt"; // gilgil temp 2015.10.28
  while (active()) {
    GPacket packet;
    packet.capture = this;
    Result res = read(&packet);
    if (res == TimeOut) continue;
    if (res == Eof || res == Fail) break;
    emit captured(&packet);
    if (this->pathType() == InPath) {
      res = relay(&packet);
      if (res != Ok) {
        qWarning() << "relay return %d" << (int)res; // gilgil temp 2015.10.29
      }
    }
  }
  qDebug() << "end"; // gilgil temp 2015.10.28
  emit closed();
}
