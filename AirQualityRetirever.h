#include <QString>
#include <QJsonDocument>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QObject>
#include

#ifndef WEATHERRETRIEVER_H
#define WEATHERRETRIEVER_H



//#include <QtMobi



class AirQualityRetriever
{
public:
    QNetworkAccessManager *manager;
    QString apikey;
    AirQualityRetriever(QString);
    QJsonDocument retrieve(double,double);
};

#endif // WEATHERRETRIEVER_H
