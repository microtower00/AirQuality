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

class Dati : public QAbstractTableModel
{
    Q_OBJECT
public:
    Dati(const QJsonObject&);
    Dati(const Dati&);

    QList<QString> getChiavi() const;
    QList<QMap<QString, double>> getDati() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool salvaJsonDati(const QString& path) const;

    static QDateTime getDateFromDouble(const double&);
    static bool isDati(const QJsonDocument&);

private:
    QList<QMap<QString, double>> dati;
    QList<QString> chiavi;
    static QStringList expectedKeys;
};

#endif // DATI_H
