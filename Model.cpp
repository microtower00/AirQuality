#include "Model.h"

Model::Model(QString apikey):aqRet(apikey){
    connect(&aqRet,SIGNAL(readReady(QJsonDocument*)),this,SLOT(saveJSonReply(QJsonDocument*)));
}

//Fa la chiamata al retriever. Non ritorna nulla perché i valori di ritorno vengono gestiti dal segnale readReady, connesso a saveJSonReply
void Model::ottieniDati(QString citta, QDate inizio, QDate fine){
    coordsResolver(citta);
    qDebug() << "Model::ottieniDati(QString,QDate,QDate)";
    aqRet.retrieveHistorical(50, 50, inizio, fine);
}

//Salva un oggetto QJSonDocument come file JSon, ed emette il segnale savedFile
void Model::saveJSonReply(QJsonDocument* doc){
    qDebug() << "Model::saveJSonReply(QJsonDocument*)";
    if(doc->isObject()){
        QJsonObject jsObj = doc->object();
        QStringList chiavi = jsObj.keys();
        qDebug()<< "filename: "<< QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

        QString filename= QString(QDateTime::currentDateTimeUtc().toString(Qt::ISODate)).append(".json");

        QFile fileRichiesta(filename);
        fileRichiesta.open(QIODevice::ReadWrite);

        fileRichiesta.write(doc->toJson());
        fileRichiesta.close();

        emit savedFile(filename);
    }
}

//Apre un file dialog, ed emette savedFile solamente se viene scelto un file
void Model::openFileDialog(QWidget* window){
    QString fileName = QFileDialog::getOpenFileName(window, "Scegli un file grafico","","File JSON (*.json)");
    if(fileName!=NULL)
        emit savedFile(fileName);
}

QGeoCoordinate Model::coordsResolver(const QString citta) const{
    //leggo il file
    QString val;
    QFile file;
    file.setFileName("worldcities.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    qWarning() << val;
    QJsonDocument json = QJsonDocument::fromJson(val.toUtf8());

    //cerco la entry di citta
    const auto entries = json["entries"];

    for (const auto entry: entries.toArray()) {
      const auto obj = entry.toObject();
      if (obj["city_ascii"] == citta) {
        qDebug() << "Longitude is" << obj["lon"];
        break;
      }
    }

}
