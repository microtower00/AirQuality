#include <QString>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>


#ifndef AIRQUALITYRETRIEVER_H
#define AIRQUALITYRETRIEVER_H

class AirQualityRetriever: public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager *manager;
    QString apikey;

public:
    AirQualityRetriever(QString="7b6bde71c02400af4d2b61da7b315b31");
    void retrieve(double,double)const;
    void retrieveHistorical(double,double,QDate,QDate)const;
    ~AirQualityRetriever();

public slots:
    QJsonDocument replyEnded(QNetworkReply*);

signals:
    void readReady(const QJsonDocument*);
};


#endif // AIRQUALITYRETRIEVER_H
