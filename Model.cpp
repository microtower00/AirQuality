#include "Model.h"

Model::Model(QString apikey):aqRet(apikey){
    connect(&aqRet,SIGNAL(readReady(QJsonDocument*)),this,SLOT(saveJSonReply(QJsonDocument*)));
}
void Model::ottieniDati(QString citta, QDate inizio, QDate fine){

    qDebug() << "Model::ottieniDati(double,double,QDate,QDate)";
    aqRet.retrieveHistorical(lat, lon, inizio, fine);
}

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

void Model::openFileDialog(QWidget* window){
    QString fileName = QFileDialog::getOpenFileName(window, "Scegli un file grafico","","File JSON (*.json)");
    emit savedFile(fileName);
}
