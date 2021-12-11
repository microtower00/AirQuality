#include "AirQualityRetriever.h"
#include<iostream>


AirQualityRetriever::AirQualityRetriever(QString apik): apikey(apik)
{
    manager = new QNetworkAccessManager();
    qInfo()<< "Costruito AqRetr";

}
//modificato tipo di ritorno a void perché non si puó ritornare nulla da uno slot
void AirQualityRetriever::retrieve(double lat, double lon){
    //Creo stringa per URL e creo URL
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution?lat=" + QString::number(lat) + "&lon=" + QString::number(lon) + "&appid=" + apikey);
    QUrl urlRichiesta(*stringaRichiesta);

    //Creo l'oggetto richiesta, non dovrebbe servire header visto che é GET
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    manager->get(*richiesta);

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

    QJsonDocument dati = QJsonDocument::fromJson(ba);
    emit readReady(&dati);
    //Non serve a nulla, a meno che lo slot non venga usato come metodo
    return dati;
}

AirQualityRetriever::~AirQualityRetriever(){}
