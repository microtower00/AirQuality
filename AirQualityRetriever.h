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
Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QString apikey;
//Non so ancora se sia giusto
public slots:
    QJsonDocument replyEnded(QNetworkReply*);

public:
    AirQualityRetriever(QString);
    QJsonDocument retrieve(double,double);
    virtual ~AirQualityRetriever();
};


#endif // WEATHERRETRIEVER_H
