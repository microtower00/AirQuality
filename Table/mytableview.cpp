#include "mytableview.h"

MyTableView::MyTableView (Dati *datiModel) : QTableView ()
{

    QStringList chiavi = datiModel->getChiavi ();

    setModel (datiModel);

    resizeColumnToContents (0);

    connect (this, SIGNAL (richiestaAggiunta()),
             this->model(), SLOT (appendRows()));
    connect (this, SIGNAL (richiestaRimossa()),
             this->model(), SLOT (removeRows()));
}
