#ifndef AIRQUALITYRETRIEVER_H
#define AIRQUALITYRETRIEVER_H

#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>

class AirQualityRetriever : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *manager;
    QString apikey;

public:
    AirQualityRetriever(QString="7b6bde71c02400af4d2b61da7b315b31");
    void retrieveHistorical(const double&, const double&, const QDate&, const QDate&)const;

public slots:
    QJsonDocument replyEnded(QNetworkReply*);

signals:
    void readReady(const QJsonDocument*);
    void erroreRichiesta(const QString&);
};

#endif // AIRQUALITYRETRIEVER_H
