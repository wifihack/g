#include "widget.h"
#include "ui_widget.h"

#include <QDialog>
#include <GJsonAux>
#include <GPropWidget>

// ----------------------------------------------------------------------------
// Widget
// ----------------------------------------------------------------------------
Widget::Widget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Widget)
{
  ui->setupUi(this);
  initializeControl();
}

Widget::~Widget()
{
  saveControl();
  finalizeControl();
  delete ui;
}

void Widget::initializeControl()
{
  move(0, 0); resize(640, 480);

  ui->mainLayout->setSpacing(0);
  ui->pteRecv->setWordWrapMode(QTextOption::NoWrap);
  ui->pteSend->setWordWrapMode(QTextOption::NoWrap);

  QObject::connect(&tcpSocket_, &QTcpSocket::connected, this, &Widget::connected);
  QObject::connect(&tcpSocket_, &QTcpSocket::disconnected, this, &Widget::disconnected);
  QObject::connect(&tcpSocket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
  QObject::connect(&tcpSocket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
  QObject::connect(&tcpSocket_, &QTcpSocket::readyRead, this, &Widget::readyRead);
  QObject::connect(&udpSocket_, &QUdpSocket::readyRead, this, &Widget::readyRead);
  QObject::connect(&sslSocket_, &QTcpSocket::connected, this, &Widget::connected);
  QObject::connect(&sslSocket_, &QTcpSocket::disconnected, this, &Widget::disconnected);
  QObject::connect(&sslSocket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error(QAbstractSocket::SocketError)));
  QObject::connect(&sslSocket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChanged(QAbstractSocket::SocketState)));
  QObject::connect(&sslSocket_, &QTcpSocket::readyRead, this, &Widget::readyRead);

  loadControl();
  setControl();
}

void Widget::finalizeControl()
{
  on_pbClose_clicked();
}

void Widget::loadControl()
{
  QJsonObject json = GJson::instance().loadFromFile();
  load(json);
}

void Widget::saveControl()
{
  QJsonObject json;
  save(json);
  GJson::instance().saveToFile(json);
}

void Widget::setControl()
{
  bool active = false;
  if (netClient_) {
    switch (netClient_->state()) {
    case QAbstractSocket::UnconnectedState: active = false; break;
    case QAbstractSocket::HostLookupState: active = true; break;
    case QAbstractSocket::ConnectingState: active = true; break;
    case QAbstractSocket::ConnectedState: active = true; break;
    case QAbstractSocket::BoundState: active = true; break;
    case QAbstractSocket::ListeningState: active = true; break;
    case QAbstractSocket::ClosingState: active = true; break;
    }
  }
  ui->pbOpen->setEnabled(!active);
  ui->pbClose->setEnabled(active);
  ui->pbSend->setEnabled(netClient_ == nullptr ? false : netClient_->state() == QAbstractSocket::ConnectedState);
}

// ----- gilgil temp 2015.07.08 -----
/*
bool Widget::event(QEvent* event)
{
  StateEvent* stateEvent = dynamic_cast<StateEvent*>(event);
  if (stateEvent != NULL)
  {
    setControl();
    return true;
  }

  MsgEvent* msgEvent = dynamic_cast<MsgEvent*>(event);
  if (msgEvent != NULL)
  {
    showMessage(msgEvent);
    return true;
  }

  CloseEvent* closeEvent = dynamic_cast<CloseEvent*>(event);
  if (closeEvent != NULL)
  {
    ui->pbClose->click();
    return true;
  }

  return QWidget::event(event);
}

void Widget::showEvent(QShowEvent* showEvent)
{
  loadControl();
  setControl();
  QWidget::showEvent(showEvent);
}

void Widget::showMessage(MsgEvent* event)
{
  static Qt::HANDLE lastThreadId = 0;
  if (lastThreadId != 0 && lastThreadId != event->threadId) event->msg = QString("\r\n") + event->msg;
  lastThreadId = event->threadId;
  ui->pteRecv->insertPlainText(event->msg);
  ui->pteRecv->ensureCursorVisible();
}
*/

void Widget::connected() {
  QString msg = "[connected] " + netClient_->peerAddress().toString() + "\r\n";
  ui->pteRecv->insertPlainText(msg);
}

void Widget::disconnected() {
  QString msg = "[disconnected] " + netClient_->peerAddress().toString() + "\r\n";
  ui->pteRecv->insertPlainText(msg);
}

void Widget::error(QAbstractSocket::SocketError socketError) {
  Q_UNUSED(socketError)
  QString msg = "[error] " + netClient_->errorString() + "\r\n";
  ui->pteRecv->insertPlainText(msg);
  setControl();
}

void Widget::stateChanged(QAbstractSocket::SocketState socketState) {
  Q_UNUSED(socketState)
  // ----- gilgil temp 2015.07.14 -----
  ///*
  QString msg = "[stateChanged] " + QString::number(socketState) + "\r\n";
  ui->pteRecv->insertPlainText(msg);
  //*/
  // ----------------------------------
  setControl();
}

void Widget::readyRead() {
  QByteArray ba = netClient_->readAll();
  if (ui->chkShowHexa->isChecked())
    ba = ba.toHex();
  ba += "\r\n";
  ui->pteRecv->insertPlainText(ba);
}

void Widget::load(QJsonObject json) {
  json["widget"] >> this;
  json["splitter"] >> ui->splitter;
  json["option"] >> option_;

  ui->chkShowHexa->setChecked(json["showHexa"].toBool());
  ui->chkSendHexa->setChecked(json["sendHexa"].toBool());
  ui->tabOption->setCurrentIndex(json["currentIndex"].toInt());
  ui->leTcpHost->setText(json["tcpHost"].toString());
  ui->leTcpPort->setText(json["tcpPort"].toString());
  ui->leUdpHost->setText(json["udpHost"].toString());
  ui->leUdpPort->setText(json["udpPort"].toString());
  ui->leSslHost->setText(json["sslHost"].toString());
  ui->leSslPort->setText(json["sslPort"].toString());
  ui->pteSend->insertPlainText(json["sendText"].toString());
}

void Widget::save(QJsonObject& json) {
  json["widget"] << this;
  json["splitter"] << ui->splitter;
  json["option"] << option_;

  json["showHexa"] = ui->chkShowHexa->isChecked();
  json["sendHexa"] = ui->chkSendHexa->isChecked();
  json["currentIndex"]= ui->tabOption->currentIndex();
  json["tcpHost"] = ui->leTcpHost->text();
  json["tcpPort"] = ui->leTcpPort->text();
  json["udpHost"] = ui->leUdpHost->text();
  json["udpPort"] = ui->leUdpPort->text();
  json["sslHost"] = ui->leSslHost->text();
  json["sslPort"] = ui->leSslPort->text();
  json["sendText"] = ui->pteSend->toPlainText();
}

void Widget::showOption(NetClient* netClient) {
  QDialog* dialog = new QDialog(this);
  QHBoxLayout* layout = new QHBoxLayout(dialog);
  GPropWidget* widget = new GPropWidget(dialog);
  widget->setObject(netClient);
  layout->addWidget(widget);
  dialog->setLayout(layout);
  dialog->exec();
}

void Widget::on_pbOpen_clicked()
{
  int currentIndex = ui->tabOption->currentIndex();
  switch (currentIndex)
  {
    case 0:
      tcpSocket_.connectToHost(ui->leTcpHost->text(), ui->leTcpPort->text().toInt());
      netClient_ = &tcpSocket_;
      break;
    case 1:
      udpSocket_.connectToHost(ui->leUdpHost->text(), ui->leUdpPort->text().toInt());
      netClient_ = &udpSocket_;
      break;
    case 2:
      sslSocket_.connectToHostEncrypted(ui->leSslHost->text(), ui->leSslPort->text().toInt());
      netClient_ = &sslSocket_;
      break;
  }
  setControl();
}

void Widget::on_pbClose_clicked()
{
  if (netClient_ != nullptr) {
    netClient_->disconnectFromHost();
    netClient_->abort();
  }
  setControl();
}

void Widget::on_pbClear_clicked()
{
  ui->pteRecv->clear();
}

void Widget::on_tbTcpAdvance_clicked()
{
  option_.tcpClient_.host_ = ui->leTcpHost->text();
  option_.tcpClient_.port_ = ui->leTcpPort->text().toInt();
  showOption(&option_.tcpClient_);
  ui->leTcpHost->setText(option_.tcpClient_.host_);
  ui->leTcpPort->setText(QString::number(option_.tcpClient_.port_));
}

void Widget::on_tbUdpAdvance_clicked()
{
  option_.udpClient_.host_ = ui->leUdpHost->text();
  option_.udpClient_.port_ = ui->leUdpPort->text().toInt();
  showOption(&option_.udpClient_);
  ui->leUdpHost->setText(option_.udpClient_.host_);
  ui->leUdpPort->setText(QString::number(option_.udpClient_.port_));
}

void Widget::on_tbSslAdvanced_clicked()
{
  option_.sslClient_.host_ = ui->leSslHost->text();
  option_.sslClient_.port_ = ui->leSslPort->text().toInt();
  showOption(&option_.sslClient_);
  ui->leSslHost->setText(option_.sslClient_.host_);
  ui->leSslPort->setText(QString::number(option_.sslClient_.port_));
}

void Widget::on_pbSend_clicked()
{
  if (netClient_ == NULL) return;
  QByteArray ba = qPrintable(ui->pteSend->toPlainText());
  ba = ba.replace("\n", "\r\n");
  if (ui->chkSendHexa->isChecked()) ba = ba.fromHex(ba);
  netClient_->write(ba);
}
