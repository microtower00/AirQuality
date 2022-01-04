#include "dataviewer.h"

void dataviewer::createTable(QJsonObject retrievedObj)
{
    QJsonArray listArray = retrievedObj["list"].toArray();

    //air quality index attualmente inutilizzato
    int aqi = listArray.at(1).toObject()["main"].toObject()["aqi"].toInt();

    //ottengo la lista dei nomi dei componenti
    QStringList componentsNames = listArray.at(1).toObject()["components"].toObject().keys();
    QStringList cols = componentsNames; //aggiungere aqi volendo

    QStringList rows;

    //ottengo la lista di date, le converto in stringhe formattate per usarle come righe
    QDateTime datetest;
    for(int i=0; i<retrievedObj["list"].toArray().size(); i++)
        rows.push_back((datetest.fromTime_t(listArray.at(i).toObject()["dt"].toInt())).toString("dd/MM/yyyy hh:mm"));

    layout = new QVBoxLayout;
    tableJS = new QTableWidget();

    mainW = new QWidget();

    mainW->setLayout(layout);

    //creo la tabella
    tableJS = new QTableWidget(rows.size(), cols.size());
    tableJS->setVerticalHeaderLabels(rows);
    tableJS->setHorizontalHeaderLabels(cols);

    //riempio la tabella scorrendo i dati
    for(int i=0; i<retrievedObj["list"].toArray().size(); i++)
        for(int j=0; j<8; j++) {
            //incommentabile dio concatenato
            QTableWidgetItem *newItem = new QTableWidgetItem(listArray.at(i).toObject()["components"].toObject().toVariantMap().values().at(j).toString());
            tableJS->setItem(i, j, newItem);
        }

    layout->addWidget(tableJS);

    setCentralWidget(mainW);

    show();
}

dataviewer::dataviewer(QWidget *parent) : QMainWindow(parent) {}
