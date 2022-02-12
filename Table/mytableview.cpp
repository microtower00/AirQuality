#include "mytableview.h"

MyTableView::MyTableView(Dati* datiModel) : QTableView() {

    QStringList chiavi = datiModel->getChiavi();

    setModel(datiModel);

    //resize(1101,900);
    resizeColumnToContents(0);

    connect(this, SIGNAL(richiestaAggiunta()), dynamic_cast<Dati*>(this->model()), SLOT(appendRows()));
    connect(this, SIGNAL(richiestaRimossa()), dynamic_cast<Dati*>(this->model()), SLOT(removeRows()));
}
