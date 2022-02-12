#ifndef CITTAEDIT_H
#define CITTAEDIT_H

#include <QCompleter>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>

class CittaEdit : public QLineEdit
{
  public:
    CittaEdit (QString, QWidget *parent = nullptr);

  private:
    QCompleter completer;
    QCompleter *createCompleter () const;
    QJsonDocument &getCitiesJson () const;
};

#endif // CITTAEDIT_H
