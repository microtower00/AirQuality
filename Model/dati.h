#ifndef DATI_H
#define DATI_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>

class Dati
{
public:
    Dati(QJsonObject);
    QList<QString> getChiavi() const;
    QList<QMap<QString, double>> getDati() const;
private:
    QList<QMap<QString, double>> dati;
    QList<QString> chiavi;
};

#endif // DATI_H
