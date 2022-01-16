#include "dataviewer.h"

void DataViewer::createTable(Dati datiModel)
{
    QList<QString> chiavi = datiModel.getChiavi();
    QList<QMap<QString, double>> dati = datiModel.getDati();

    int rowsSize = dati.size();

    //costruisco la tabella e assegno gli header
    tableJS = new QTableWidget(rowsSize, chiavi.size());
    tableJS->setHorizontalHeaderLabels(chiavi);

    //riempio la tabella
    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        for(auto itChiavi = chiavi.begin(); itChiavi!=chiavi.end(); ++itChiavi) {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(itDati->value(*itChiavi)));
            tableJS->setItem(std::distance(dati.begin(), itDati), std::distance(chiavi.begin(), itChiavi), newItem);
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

DataViewer::DataViewer(QWidget *parent) : QMainWindow(parent) {
    qDebug()<<"Doveo el clacson";
}
