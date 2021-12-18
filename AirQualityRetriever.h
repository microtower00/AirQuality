#include <QString>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>
//#include <QVariant>


#ifndef WEATHERRETRIEVER_H
#define WEATHERRETRIEVER_H

class AirQualityRetriever: public QObject{
Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QString apikey;
public:
    AirQualityRetriever(QString);
    void retrieve(double,double);
    void retrieveHistorical(double,double,QDate,QDate);
    virtual ~AirQualityRetriever();

public slots:
    QJsonDocument replyEnded(QNetworkReply*);
signals:
    void readReady(QJsonDocument*);

};


#endif // WEATHERRETRIEVER_H
