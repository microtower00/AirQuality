#include <QString>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QObject>

#ifndef WEATHERRETRIEVER_H
#define WEATHERRETRIEVER_H



//#include <QtMobi



class AirQualityRetriever: public QObject{
//Non so ancora se sia giusto
/*public slots:
    QJsonDocument replyEnded();*/

public:
    QNetworkAccessManager *manager;
    QString apikey;
    AirQualityRetriever(QString);
    QJsonDocument retrieve(double,double);
};

#endif // WEATHERRETRIEVER_H
