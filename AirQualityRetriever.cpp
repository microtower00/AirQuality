#include "AirQualityRetriever.h"
#include<iostream>


AirQualityRetriever::AirQualityRetriever(QString apik): apikey(apik)
{
    manager = new QNetworkAccessManager();
    qInfo()<< "Costruito AqRetr";

}

QJsonDocument AirQualityRetriever::retrieve(double lat, double lon){
    //Creo stringa per URL e creo URL
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution?lat=50&lon=50&appid=7b6bde71c02400af4d2b61da7b315b31");
    QUrl urlRichiesta(*stringaRichiesta);

    //Creo l'oggetto richiesta, non dovrebbe servire header visto che é GET
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    /*QNetworkReply *response = */manager->get(*richiesta);

    //Collego segnale di richiesta finita allo slot apposito
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyEnded(QNetworkReply*)));

}

QJsonDocument AirQualityRetriever::replyEnded(QNetworkReply* response){
    //qDebug() << "Richiesta terminata: "<< response->isFinished();
    QByteArray ba;
    if(response->error()==QNetworkReply::NoError){
         ba = response->readAll();
         qDebug() << "Leggo risposta";
    }else
        qDebug() << response->error();

    response->deleteLater();
    //DIOP VA
    QString risposta= QString(ba);
    qDebug() << risposta;
    //Non serve a nulla
    return QJsonDocument::fromJson(ba);
}

AirQualityRetriever::~AirQualityRetriever(){}
