#include "airqualityretriever.h"


AirQualityRetriever::AirQualityRetriever(QString apik): apikey(apik)
{
    manager = new QNetworkAccessManager();
    qInfo()<< "Costruito AqRetr";

    //Collego segnale di richiesta finita allo slot apposito
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyEnded(QNetworkReply*)));

}

//modificato tipo di ritorno a void perché non si puó ritornare nulla da uno slot
void AirQualityRetriever::retrieve(double lat, double lon) const {
    //Creo stringa per URL e creo URL
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution?lat=" + QString::number(lat) + "&lon=" + QString::number(lon) + "&appid=" + apikey);
    QUrl urlRichiesta(*stringaRichiesta);

    //Creo l'oggetto richiesta, non dovrebbe servire header visto che é GET
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    manager->get(*richiesta);
}

void AirQualityRetriever::retrieveHistorical(double lat, double lon, QDate start, QDate end) const {
    //Creo stringa per URL e creo URL
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution/history?lat=" + QString::number(lat) + "&lon=" + QString::number(lon) + "&start=" + QString::number((new QDateTime(start))->toTime_t()) + "&end=" + QString::number((new QDateTime(end))->toTime_t()) + "&appid=" + apikey);
    QUrl urlRichiesta(*stringaRichiesta);

    qDebug()<<"AQR::retrieveHistorical(double,double,QDate,QDate)";

    //Creo l'oggetto richiesta
    QNetworkRequest *richiesta = new QNetworkRequest(urlRichiesta);

    //Invio richiesta
    manager->get(*richiesta);
}

//Slot per acchiappare la richiesta appena finita
QJsonDocument AirQualityRetriever::replyEnded(QNetworkReply* response){
    QByteArray ba;
    if(response->error()==QNetworkReply::NoError)
        ba = response->readAll();
    else
        qDebug() << response->error();

    response->deleteLater();

    //emetto un sengale prendibile da chi vuole leggere il file json
    QJsonDocument dati = QJsonDocument::fromJson(ba);
    qDebug()<<"emit readReady(QNetworkReply*)";
    emit readReady(&dati);

    //Non serve a nulla, a meno che lo slot non venga usato come metodo
    return dati;
}

AirQualityRetriever::~AirQualityRetriever(){}

