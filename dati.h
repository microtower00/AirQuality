#ifndef DATI_H
#define DATI_H

#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QDateTime>
#include <QAbstractTableModel>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

#include "coordinate.h"

class Dati : public QAbstractTableModel
{
    Q_OBJECT
public:
    Dati(const QJsonObject&, const QDateTime& = QDateTime(), const Coordinate& = Coordinate(0,0));
    Dati(const Dati&);

    QList<QString> getChiavi() const;
    QList<QMap<QString, double>> getDati() const;
    static QDateTime getDateFromDouble(const double&);
    static bool isDati(const QJsonDocument&);
    bool salvaJsonDati(const QString& path) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

public slots:
    bool appendRows(unsigned int count=1);
    bool removeRows(unsigned int count=1);

private:
    QList<QMap<QString, double>> dati;
    QList<QString> chiavi;
    Coordinate coords;
    static QStringList expectedKeys;
};

#endif // DATI_H
