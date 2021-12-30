#include "AirQualityRetriever.h"
//#include<iostream>


AirQualityRetriever::AirQualityRetriever(QString apik): apikey(apik)
{
    manager = new QNetworkAccessManager();
    //qInfo()<< "Costruito AqRetr";

    //Collego segnale di richiesta finita allo slot apposito
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyEnded(QNetworkReply*)));

}

AirQualityRetriever::AirQualityRetriever(const AirQualityRetriever& ret){
    this->apikey=ret.apikey;
}
//modificato tipo di ritorno a void perché non si puó ritornare nulla da uno slot
void AirQualityRetriever::retrieve(double lat, double lon)const{
    //Creo stringa per URL e creo URL
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution?lat=" + QString::number(lat) + "&lon=" + QString::number(lon) + "&appid=" + apikey);
    QUrl urlRichiesta(*stringaRichiesta);

    //Creo l'oggetto richiesta, non dovrebbe servire header visto che é GET
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    manager->get(*richiesta);
}

void AirQualityRetriever::retrieveHistorical(double lat, double lon, QDate start, QDate end)const{
    //Creo stringa per URL e creo URL

    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution/history?lat=" + QString::number(lat) + "&lon=" + QString::number(lon) + "&start=" + QString::number((new QDateTime(start))->toTime_t()) + "&end=" + QString::number((new QDateTime(end))->toTime_t()) + "&appid=" + apikey);
    QUrl urlRichiesta(*stringaRichiesta);
    //qDebug() << "stringa richiesta"<<*stringaRichiesta;

    //Creo l'oggetto richiesta, non dovrebbe servire header visto che é GET
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    manager->get(*richiesta);
}

//Slot per acchiappare la richiesta appena finita
QJsonDocument AirQualityRetriever::replyEnded(QNetworkReply* response){
    //qDebug() << "Richiesta terminata: "<< response->isFinished();
    QByteArray ba;
    if(response->error()==QNetworkReply::NoError){
         ba = response->readAll();
         //qDebug() << "Leggo risposta";
    }else
        qDebug() << response->error();

    response->deleteLater();

    //QString risposta= QString(ba);
    //qDebug() << risposta;

    //emetto un sengale prendibile da chi vuole leggere il file json
    QJsonDocument dati = QJsonDocument::fromJson(ba);
    emit readReady(&dati);

    // Stampa la stessa porcheria con dati.object()["coord"]
    // Volevo provare a ottenere solo una delle due coordinate ma per adesso non riesco
    //qDebug() << *dati.object().find("coord");

    //Non serve a nulla, a meno che lo slot non venga usato come metodo
    return dati;
}

AirQualityRetriever::~AirQualityRetriever(){}

