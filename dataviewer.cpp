#include "dataviewer.h"

void dataviewer::createTable(QJsonObject retrievedObj)
{
    QJsonArray listArray = retrievedObj.value("list").toArray();
    QStringList componentsNames = listArray.at(1).toObject().value("components").toObject().keys();

    //singola riga, una mappa con coppie chiave:valore
    QMap<QString, double> singleRow;

    //Creo e riempio la lista di chiavi con data e aqi oltre ai componenti
    QStringList chiavi;
    chiavi.push_back("Data");
    for(auto it=componentsNames.begin(); it!=componentsNames.end(); ++it) chiavi.push_back(*it);
    chiavi.push_back("aqi");

    //numero di righe
    unsigned int rowsSize = listArray.size();

    //ogni riga è una mappa, l'insieme delle righe è una lista di mappe
    QList<QMap<QString, double>> rows;

    //riempio le singole righe e l'insieme di righe
    for(unsigned int i=0; i<rowsSize; ++i) {
        for(auto it = chiavi.begin(); it!=chiavi.end(); ++it) {
            if(*it=="Data") singleRow.insert(*it, listArray.at(i).toObject().value("dt").toDouble());
            else if(*it=="aqi") singleRow.insert(*it, listArray.at(i).toObject().value("main").toObject().value("aqi").toDouble());
            else singleRow.insert(*it, listArray.at(i).toObject().value("components").toObject().value(*it).toDouble());
        }
        rows.push_back(singleRow);
    }

    //costruisco la tabella e assegno gli header
    tableJS = new QTableWidget(rowsSize, chiavi.size());
    tableJS->setHorizontalHeaderLabels(chiavi);

    //riempio la tabella
    for(auto itR = rows.begin(); itR!=rows.end(); ++itR) {
        for(auto itC = chiavi.begin(); itC!=chiavi.end(); ++itC) {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(itR->value(*itC)));
            tableJS->setItem(std::distance(rows.begin(), itR), std::distance(chiavi.begin(), itC), newItem);
        }
    }

    layout = new QVBoxLayout;

    mainW = new QWidget();

    mainW->setLayout(layout);

    layout->addWidget(tableJS);

    setCentralWidget(mainW);
    resize(1000,500);
    show();
}

dataviewer::dataviewer(QWidget *parent) : QMainWindow(parent) {
    qDebug()<<"Doveo el clacson";
}
