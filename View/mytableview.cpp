#include "mytableview.h"

MyTableView::MyTableView(Dati& datiModel) : QTableView() {
    setModel(&datiModel);
    //rip header non si vuole mostrare
    horHeader = new QHeaderView(Qt::Horizontal);
    horHeader->setModel(&datiModel);
    qDebug()<<horHeader;
    setHorizontalHeader(horHeader);
    horizontalHeader()->setVisible(true);
}
