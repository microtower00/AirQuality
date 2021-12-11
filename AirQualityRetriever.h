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
public:
    AirQualityRetriever(QString);
    void retrieve(double,double);
    virtual ~AirQualityRetriever();

public slots:
    QJsonDocument replyEnded(QNetworkReply*);
signals:
    void readReady(QJsonDocument*);

};


#endif // WEATHERRETRIEVER_H
