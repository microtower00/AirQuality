#include "Model.h"

Model::Model(QString apikey):aqRet(apikey){
    connect(&aqRet,SIGNAL(readReady(QJsonDocument*)),this,SLOT(readingJSon(QJsonDocument*)));
}

void Model::getAirQuality(double lat, double lon){
    aqRet.retrieve(lat, lon);
    qDebug() << "Model::getAirQuality(double,double)";
}
void Model::getAirQuality(double lat, double lon,QDate inizio,QDate fine){
    aqRet.retrieveHistorical(lat,lon,inizio,fine);
}

void Model::readingJSon(QJsonDocument* doc){
    if(doc->isObject()){
        QJsonObject jsObj = doc->object();
        QStringList chiavi = jsObj.keys();

        QFile fileRichiesta(QDateTime::currentDateTime().toString());
        fileRichiesta.open(QIODevice::ReadWrite);

        fileRichiesta.write(doc->toJson());
    }
}
