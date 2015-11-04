#include <QApplication>
#include <GJsonAux>
#include <GPropWidget>

#include "party.h"
#include "person.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QJsonObject json = GJson::instance().loadFromFile();
  QJsonObject partyJson = json["party"].toObject();
  QJsonObject widgetJson = json["widget"].toObject();

  Party party;
  //Person party;
  party.load(partyJson);

  GPropWidget widget;
  widgetJson >> &widget;
  widget.setObject(&party);
  widget.show();
  int res = a.exec();

  party.save(partyJson);
  widgetJson << &widget;
  json["party"] = partyJson;
  json["widget"] = widgetJson;
  GJson::instance().saveToFile(json);

  return res;
}

