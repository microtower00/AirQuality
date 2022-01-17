#ifndef DATI_H
#define DATI_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>

class Dati
{
public:
    Dati(QJsonObject);
    QList<QString> getChiavi() const;
    QList<QMap<QString, double>> getDati() const;
    QDateTime getDateFromDouble(double) const;
private:
    QList<QMap<QString, double>> dati;
    QList<QString> chiavi;
};

#endif // DATI_H
