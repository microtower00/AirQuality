#include "AirQualityRetriever.h"
#include<iostream>


AirQualityRetriever::AirQualityRetriever(QString apik): apikey(apik)
{
    manager = new QNetworkAccessManager();
    qInfo()<< "Costruito AqRetr";
    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}
/*
QJsonDocument replyEnded(){
    qDebug()<<"Si muove qualcosa";
}*/

QJsonDocument AirQualityRetriever::retrieve(double lat, double lon){
    //Creo stringa per URL e creo URL
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution?lat=50&lon=50&appid=7b6bde71c02400af4d2b61da7b315b31");
    QUrl urlRichiesta(*stringaRichiesta);

    //Creo l'oggetto richiesta, non dovrebbe servire header visto che é GET
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    QNetworkReply *response = manager->get(*richiesta);

    qDebug() << response->error();
    qDebug() << response->isFinished();

    //Va fatto con segnali e slot ma non riesco
    //connect(response, SIGNAL(finished()),this, SLOT(replyEnded()));

    //qInfo()<< "Preciclo";

    //Questo ciclo non va
    while (response->isFinished()){}
    if(response->error()!=QNetworkReply::NoError){
        qDebug() << response->error();
    }
    //qDebug() << response->error();

    //Parso da ByteArray a JSonDocument, funziona ma viene fatto senza attendere che la risposta sia comletata, devo fixare
    QByteArray ba = response->readAll();
    QString responseString(ba);
    //qDebug() << responseString;
    return QJsonDocument::fromJson(ba);;
}
