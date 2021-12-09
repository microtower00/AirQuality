

AirQualityRetriever::AirQualityRetriever(QString apik): apikey(apik)
{
    manager = new QNetworkAccessManager();
    //connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

}

QJsonDocument AirQualityRetriever::retrieve(double lat, double lon){
    QString *stringaRichiesta = new QString("http://api.openweathermap.org/data/2.5/air_pollution?lat=50&lon=50&appid=7b6bde71c02400af4d2b61da7b315b31");
    QUrl urlRichiesta(*stringaRichiesta);
    QNetworkReply *prova = manager->get(QNetworkRequest(urlRichiesta));

    QObject::connect(prova, &QNetworkReply::finished, [=]() {

        if(prova->error() == QNetworkReply::NoError)
        {
            QByteArray response = prova->readAll();
            QTextStream ts(stdout);
               ts << "rendered JSON";
               ts << response;

            //QJsonObject rootObj = document.object();
        }
        else // handle error
        {
          qDebug("DioAsSaSs");
        }
    });
}
