#include "dati.h"
QStringList Dati::expectedKeys = {"co","nh3","no","no2","o3","pm10","pm2_5","so2"};
Dati::Dati(const QJsonObject& retrievedObj) {
    QJsonArray listArray = retrievedObj.value("list").toArray();
    QStringList componentsNames = listArray.at(1).toObject().value("components").toObject().keys();

    //singola riga, una mappa con coppie chiave:valore
    QMap<QString, double> singleRow;

    //Riempio la lista di chiavi con data e aqi oltre ai componenti
    chiavi.push_back("Data");

    for(auto comp:componentsNames)
        chiavi.push_back(comp);

    chiavi.push_back("aqi");

    //numero di righe
    unsigned int rowsSize = listArray.size();

    //riempio le singole righe e l'insieme di righe
    for(unsigned int i=0; i<rowsSize; ++i) {
        for(auto chiave:chiavi) {
            if(chiave=="Data") singleRow.insert(chiave, listArray.at(i).toObject().value("dt").toDouble());
            else if(chiave=="aqi") singleRow.insert(chiave, listArray.at(i).toObject().value("main").toObject().value("aqi").toDouble());
            else singleRow.insert(chiave, listArray.at(i).toObject().value("components").toObject().value(chiave).toDouble());
        }
        dati.push_back(singleRow);
    }
}

bool Dati::salvaJsonDati(const QString& path) const{
    QJsonArray listArray;

    QJsonObject componente, temp, fileObj, elemArray;
    temp.insert("lat", 0);
    temp.insert("lon",0);

    componente.insert("coord",temp);
    fileObj.insert("coord",temp);

    for(auto entry : getDati()){
        componente = QJsonObject();
        for(QString chiave : entry.keys()){
            if(chiave=="Data"){
                elemArray.insert("dt", entry.value(chiave));
            }else if(chiave=="aqi"){
                temp = QJsonObject();
                temp.insert("aqi",entry.value(chiave));
                elemArray.insert("main",temp);
            }else if(chiave!="Data"||chiave!="aqi"){
                componente.insert(chiave,entry.value(chiave));
            }
        }
        elemArray.insert("components",componente);
        listArray.append(elemArray);

    }
    fileObj.insert("list", listArray);
    try{
        QFile fileJson(path);

        fileJson.resize(0);
        fileJson.open(QIODevice::WriteOnly);
        fileJson.write(QJsonDocument(fileObj).toJson());

        fileJson.close();
        return true;
    }catch (std::exception) {
        qDebug()<<"Qualcosa è andato storto nell'apertura del file";
        return false;
    }
}
Dati::Dati(const Dati& d2) : dati(d2.dati), chiavi(d2.chiavi) {}

QList<QString> Dati::getChiavi() const{
    return chiavi;
}

QList<QMap<QString, double>> Dati::getDati() const{
    return dati;
}

QDateTime Dati::getDateFromDouble(const double& dataDouble) {
    return QDateTime::fromTime_t(static_cast<int>(dataDouble));
}

int Dati::rowCount(const QModelIndex &parent) const {
    if(parent.isValid()) return 0;

    return dati.size();
}

int Dati::columnCount(const QModelIndex &parent) const {
    if(parent.isValid()) return 0;

    return chiavi.size();
}

QVariant Dati::data(const QModelIndex &index, int role) const {
    if(index.isValid() && (role==Qt::DisplayRole || role==Qt::EditRole)) {
        if(index.column()!=0)
            return dati.at(index.row()).values().at(index.column());
        else return getDateFromDouble(dati.at(index.row()).values().at(index.column()));
    }
    else return QVariant();
}

QVariant Dati::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return QVariant();

    if(orientation==Qt::Horizontal) return dati.first().keys().at(section);

    if(orientation==Qt::Vertical) return section;

    return QVariant();
}

bool Dati::isDati(const QJsonDocument& doc){
    if(!(doc.isNull()||doc.isEmpty())){
        //contiene coords e list
        if(doc.object().contains("coord") && doc.object().contains("list")){
            QJsonArray listArray = doc.object().value("list").toArray();

            //per ogni elemento di list controllo che abbia components, main e dt
            for(int i = 0; i < listArray.size(); ++i){
                //qDebug()<<"Controllo la lista";
                if(!(listArray.at(i).toObject().contains("components") && listArray.at(i).toObject().contains("dt") && listArray.at(i).toObject().contains("main"))){
                    //qDebug()<<"Non contiene main, components e dt";
                    return false;
                } else {
                    QJsonObject componenti = listArray.at(i).toObject().value("components").toObject();
                    for(QString componente:expectedKeys){
                        if(!componenti.contains(componente)){
                            //qDebug()<<"Non ha tutta la robba";
                            return false;
                        }
                    }
                   return true;
                }
            }
        }else
        //qDebug()<<"Non contiene list";
        return false;
    }
    //qDebug()<<"è nullo o empty";
    return false;
}

Qt::ItemFlags Dati::flags(const QModelIndex &index) const {
    //Q_UNUSED(index);
    if(index.column()>0)
        return {Qt::ItemIsEnabled, Qt::ItemIsEditable};
    else return {Qt::ItemIsEnabled};
}

bool Dati::setData(const QModelIndex &index, const QVariant &value, int role) {
    if(role==Qt::EditRole) {
        if(index.column()>1 || (index.column()==1 && value==int(value.toUInt()) && value<=5 && value>=0)) {
            dati[index.row()].insert(dati[index.row()].keys().at(index.column()), value.toDouble());
            emit dataChanged(index, index, {Qt::EditRole});
            return true;
        }
    } else {
        return false;
    }
}

bool Dati::appendRows(unsigned int count) {
    QMap<QString, double> nuovaRiga;

    beginInsertRows(QModelIndex(), dati.size(), dati.size());

    for(unsigned int i=0; i<count; ++i) {
        //qDebug()<<"Size: "<<dati.size()<<" Riga-1+i: "<<dati.size()-1+i;
        nuovaRiga.insert("Data", dati.at(dati.size()-1).value("Data")+3600);

        for(auto it=chiavi.begin()+1; it!=chiavi.end(); ++it) {
            nuovaRiga.insert(*it, 0);
        }
        dati.insert(dati.size(), nuovaRiga);
    }

    endInsertRows();
    return true;
}

