#include "airqualityretriever.h"

AirQualityRetriever::AirQualityRetriever (QString apik) : apikey (apik)
{
    manager = new QNetworkAccessManager ();
    connect (manager, SIGNAL (finished (QNetworkReply *)), this,
             SLOT (replyEnded (QNetworkReply *)));
}

void
AirQualityRetriever::retrieveHistorical (const double &lat, const double &lon,
                                         const QDate &start,
                                         const QDate &end) const
{
    QString *stringaRichiesta = new QString (
        "http://api.openweathermap.org/data/2.5/air_pollution/history?lat="
        + QString::number (lat) + "&lon=" + QString::number (lon)
        + "&start=" + QString::number ((new QDateTime (start))->toTime_t ())
        + "&end=" + QString::number ((new QDateTime (end))->toTime_t ())
        + "&appid=" + apikey);
    QUrl urlRichiesta (*stringaRichiesta);
    QNetworkRequest *richiesta = new QNetworkRequest (urlRichiesta);
    manager->get (*richiesta);
}

QJsonDocument
AirQualityRetriever::replyEnded (QNetworkReply *response)
{
    if (response->error () == QNetworkReply::NoError)
        {
            QByteArray ba = response->readAll ();
            response->deleteLater ();
            QJsonDocument dati = QJsonDocument::fromJson (ba);
            emit readReady (&dati);
            return dati;
        }
    else
        {
            emit erroreRichiesta (
                "Errore nella richiesta. Prova a controllare la connessione.");
            return QJsonDocument ();
        }
}
