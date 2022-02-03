#include "dati.h"

Dati::Dati(QJsonObject retrievedObj)
{
    QJsonArray listArray = retrievedObj.value("list").toArray();
    QStringList componentsNames = listArray.at(1).toObject().value("components").toObject().keys();

    //singola riga, una mappa con coppie chiave:valore
    QMap<QString, double> singleRow;

    //Riempio la lista di chiavi con data e aqi oltre ai componenti
    chiavi.push_back("Data");

    for(auto it:componentsNames)
        chiavi.push_back(it);

    chiavi.push_back("aqi");

    //numero di righe
    unsigned int rowsSize = listArray.size();

    //riempio le singole righe e l'insieme di righe
    for(unsigned int i=0; i<rowsSize; ++i) {
        for(auto it:chiavi) {
            if(it=="Data") singleRow.insert(it, listArray.at(i).toObject().value("dt").toDouble());
            else if(it=="aqi") singleRow.insert(it, listArray.at(i).toObject().value("main").toObject().value("aqi").toDouble());
            else singleRow.insert(it, listArray.at(i).toObject().value("components").toObject().value(it).toDouble());
        }
        dati.push_back(singleRow);
    }
}

QList<QString> Dati::getChiavi() const{
    return chiavi;
}

QList<QMap<QString, double>> Dati::getDati() const{
    return dati;
}

QDateTime Dati::getDateFromDouble(double dataDouble) {
    return QDateTime::fromTime_t(static_cast<int>(dataDouble));
}
