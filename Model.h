#ifndef MODEL_H
#define MODEL_H

#include <AirQualityRetriever.h>
#include <QFile>

class Model: public QObject
{
public:
    Model(QString);
public slots:
    void getAirQuality(double,double);
    void getAirQuality(double,double,QDate,QDate);

    void readingJSon(QJsonDocument*);

private:
    AirQualityRetriever aqRet;
};

#endif // MODEL_H
