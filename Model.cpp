#include "Model.h"

Model::Model(QString apikey):aqRet(apikey){
    connect(&aqRet,SIGNAL(readReady(const QJsonDocument*)),this,SLOT(saveJSonReply(const QJsonDocument*)));
}

//Fa la chiamata al retriever. Non ritorna nulla perché i valori di ritorno vengono gestiti dal segnale readReady, connesso a saveJSonReply
void Model::ottieniDati(QString citta, QDate inizio, QDate fine) const{
    QGeoCoordinate coords_citta = coordsResolver(citta);
    qDebug() << "Model::ottieniDati(QString,QDate,QDate)";
    aqRet.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
}

//Salva un oggetto QJSonDocument come file JSon, ed emette il segnale savedFile
void Model::saveJSonReply(const QJsonDocument* doc) const{
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

        emit savedFile(QCoreApplication::applicationDirPath()+filename);
    }
}

//Apre un file dialog, ed emette savedFile solamente se viene scelto un file
void Model::openFileDialog(QWidget* window) const{
    QString fileName = QFileDialog::getOpenFileName(window, "Scegli un file grafico","","File JSON (*.json)");
    if(fileName!=NULL)
        emit savedFile(fileName);
    qDebug()<<fileName;
}

//Capire cosa ritornare se la cittá non viene trovata, Eccezione?
QGeoCoordinate Model::coordsResolver(const QString citta) const{
    //leggo il file
    //qDebug()<< "Model::coordsResolver(const QString citta) const";
    QString val;
    QFile file;
    file.setFileName("worldcities.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(val.toLocal8Bit());
    if(json.isNull())
        qDebug()<<"Can't open "+file.fileName()+": it is not a JSON document";
    if(!json.isArray())
        qDebug()<< file.fileName()+" is not/doesn't contain a JSON array";
    QJsonArray json_array = json.array();
    if(json_array.isEmpty()){
        qDebug() << "The array is empty";
    }

    //ottengo le coordinate
    QJsonValue json_obj;

    //cerco in tutto l'array
    for(int i=0; i< json_array.count(); ++i){
        json_obj = json_array.at(i).toObject();
        if(json_obj["city_ascii"]==citta){
            return QGeoCoordinate(json_obj["lat"].toDouble(),json_obj["lng"].toDouble());
        }
    }
}

//Ritorrna tutte le citta contenute sotto la chiave "city_ascii" nel file worldcities.json
QStringList Model::getCompleterList() const{
    //stesso codice per aprire di coordsResolver, magari riutilizzare
    QStringList listaCitta;
    QString val;
    QFile file;
    file.setFileName("worldcities.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument json = QJsonDocument::fromJson(val.toLocal8Bit());
    if(json.isNull())
        qDebug()<<"Can't open "+file.fileName()+": it is not a JSON document";
    if(!json.isArray())
        qDebug()<< file.fileName()+" is not/doesn't contain a JSON array";
    QJsonArray json_array = json.array();
    if(json_array.isEmpty()){
        qDebug() << "The array is empty";
    }

    //ottengo le cittá
    QJsonValue json_obj;

    //cerco in tutto l'array
    for(int i=0; i< json_array.count(); ++i){
        listaCitta.append(json_array.at(i).toObject()["city_ascii"].toString());
    }
    //qDebug()<< listaCitta;
    return listaCitta;
}
