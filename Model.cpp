//DEPRECATO
#include "Model.h"

const QString Model::APIKEY = "7b6bde71c02400af4d2b61da7b315b31";

Model::Model(QString api):mainwindow(), data(), aqRet(api){
    qDebug()<<"costruisco il model";
    mainwindow.show();
    //Quando il retriever ha finito di leggere la risposta, salvala
    connect(&aqRet,SIGNAL(readReady(const QJsonDocument*)),this,SLOT(saveJSonReply(const QJsonDocument*)));
    connect(&mainwindow, SIGNAL(needDati(QString,QDate,QDate)),this,SLOT(ottieniDati(QString,QDate,QDate)));
    setViewCompleter();
    if(data==0)
        qDebug()<<"Su sta merda de camion";
    data = new dataviewer;
    connect(this, SIGNAL(savedObj(QJsonObject)), data, SLOT(createTable(QJsonObject)));
}

//Fa la chiamata al retriever. Non ritorna nulla perché i valori di ritorno vengono gestiti dal segnale readReady, connesso a saveJSonReply
void Model::ottieniDati(QString citta, QDate inizio, QDate fine) const{
    //senza la riga sottostante crasha se non viene messa la città, non ha nessun senso
    //in più prende londra in totale autonomia senza che sia specificato da nessuna parte
    citta.isNull() ? qDebug()<<"null" : qDebug()<<"OK";
    QGeoCoordinate coords_citta = coordsResolver(citta);
    qDebug() << "Model::ottieniDati(QString,QDate,QDate)";

    QDate inizioAPI = inizioAPI.fromString("2020-11-27", Qt::ISODate);

    if(inizio>=inizioAPI && fine<=QDate::currentDate() && fine>inizio)
        aqRet.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
    else throw std::invalid_argument("Date non valide");
}

//Salva un oggetto QJSonDocument come file JSon, ed emette il segnale savedFile
void Model::saveJSonReply(const QJsonDocument* doc) const{
    qDebug() << "Model::saveJSonReply(QJsonDocument*)";
    if(doc->isObject()){
        QJsonObject jsObj = doc->object();
        //commentato perchè non in uso
        //QStringList chiavi = jsObj.keys();
        qDebug()<< "filename: "<< QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

        QString filename= QString(QDateTime::currentDateTimeUtc().toString(Qt::ISODate)).append(".json");

        QFile fileRichiesta(filename);
        fileRichiesta.open(QIODevice::ReadWrite);

        fileRichiesta.write(doc->toJson());
        fileRichiesta.close();

        //segnale aggiunto per comodita nella creazione della tabella
        emit savedObj(jsObj);
        //emit savedFile(QCoreApplication::applicationDirPath()+filename);
    }
}
//DEPRECATO
//Apre un file dialog, ed emette savedFile solamente se viene scelto un file
void Model::openFileDialog(QWidget* window) const{
    QString fileName = QFileDialog::getOpenFileName(window, "Scegli un file grafico","","File JSON (*.json)");
    if(fileName!=NULL){
        //emit savedFile(fileName);
        emit savedObj(openJSon(fileName).object());
    }
}
//DEPRECATO
QJsonDocument Model::openJSon(QString relativePath) const{
    QString val;
    QFile file;

    file.setFileName(relativePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument json = QJsonDocument::fromJson(val.toLocal8Bit());
    if(json.isNull())
        throw std::invalid_argument("Il file che si sta cercando di aprire non é valido");
    return json;
}
//DEPRECATO
QJsonDocument Model::apriWC() const {
    QJsonDocument json = openJSon("worldcities.json");

    if(!json.isArray())
        throw std::invalid_argument("Il file che si sta cercando di aprire non contiene un JSON");

    QJsonArray json_array = json.array();

    if(json_array.isEmpty()){
        qDebug() << "L'array è vuoto";
    }

    return json;
}
//DEPRECATO
QGeoCoordinate Model::coordsResolver(const QString citta) const{
    //ottengo le coordinate
    QJsonObject json_obj;

    QJsonArray json_array = apriWC().array();

    //cerco in tutto l'array
    for(int i=0; i< json_array.count(); ++i){
        json_obj = json_array.at(i).toObject();
        if(json_obj["city_ascii"]==citta){
            return QGeoCoordinate(json_obj["lat"].toDouble(),json_obj["lng"].toDouble());
        }
    }
    throw std::domain_error("La città inserita non è disponibile");
}
//DEPRECATO
//Ritorna tutte le citta contenute sotto la chiave "city_ascii" nel file worldcities.json
void Model::setViewCompleter(){
    QStringList listaCitta;
    QJsonArray json_array = apriWC().array();

    //cerco in tutto l'array
    for(int i=0; i<json_array.count(); ++i)
        listaCitta.append(json_array.at(i).toObject()["city_ascii"].toString());

    mainwindow.setCompleterList(listaCitta);
}
