#include "mytableview.h"

MyTableView::MyTableView(Dati& datiModel) : QTableView() {
    QStringList chiavi = datiModel.getChiavi();
    for(auto chiave:chiavi)
        datiModel.setHeaderData(chiavi.indexOf(chiave), Qt::Horizontal, chiave, Qt::DisplayRole);

    setModel(&datiModel);

    resize(1101,750);
    resizeColumnToContents(0);
}
