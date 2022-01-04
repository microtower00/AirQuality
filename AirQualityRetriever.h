#include <QString>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>


#ifndef WEATHERRETRIEVER_H
#define WEATHERRETRIEVER_H

class AirQualityRetriever: public QObject{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QString apikey;
public:
    AirQualityRetriever(QString);
    AirQualityRetriever(const AirQualityRetriever&);
    void retrieve(double,double)const;
    void retrieveHistorical(double,double,QDate,QDate)const;
    ~AirQualityRetriever();

public slots:
    QJsonDocument replyEnded(QNetworkReply*);
signals:
    void readReady(const QJsonDocument*);

};


#endif // WEATHERRETRIEVER_H
