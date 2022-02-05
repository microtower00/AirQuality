#include "dataviewer.h"

DataViewer::DataViewer(Dati datiModel) : QTableWidget() {
    QList<QString> chiavi = datiModel.getChiavi();
    QList<QMap<QString, double>> dati = datiModel.getDati();

    int rowsSize = dati.size();

    setRowCount(rowsSize);
    setColumnCount(chiavi.size());
    setHorizontalHeaderLabels(chiavi);

    //riempio la tabella
    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        for(auto itChiavi = chiavi.begin(); itChiavi!=chiavi.end(); ++itChiavi) {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(itDati->value(*itChiavi)));
            setItem(std::distance(dati.begin(), itDati), std::distance(chiavi.begin(), itChiavi), newItem);
        }
    }

    //size

    //resize(1000,500);

    //emit tablePronta();
}
