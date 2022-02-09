#include "mytableview.h"

MyTableView::MyTableView(Dati& datiModel) : QTableView() {

    QStringList chiavi = datiModel.getChiavi();

    setModel(&datiModel);

    resize(1101,750);
    resizeColumnToContents(0);

    connect(this, SIGNAL(richiestaAggiunta()), dynamic_cast<Dati*>(this->model()), SLOT(appendRows()));
}
