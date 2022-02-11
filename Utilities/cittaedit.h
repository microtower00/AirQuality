#ifndef CITTAEDIT_H
#define CITTAEDIT_H

#include <QLineEdit>
#include <QCompleter>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>

class CittaEdit : public QLineEdit
{
public:
    CittaEdit(QString, QWidget* parent = nullptr);
private:
    QCompleter completer;
    QCompleter* createCompleter()const;
    QJsonDocument& getCitiesJson() const;
};

#endif // CITTAEDIT_H
