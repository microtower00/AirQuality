#include "tablechooser.h"

TableChooser::TableChooser (Dati *dati) : data (dati)
{
    mainLayout = new QVBoxLayout ();

    pbTabella = new QPushButton ("Visualizza tabella con tutti i dati");
    pbAddRiga = new QPushButton ("Aggiungi una riga in coda");
    pbRemRiga = new QPushButton ("Rimuovi l'ultima riga");
    pbSalvaFile = new QPushButton ("Salva i dati correnti");

    pbAddRiga->setEnabled (false);
    pbRemRiga->setEnabled (false);

    mainLayout->addWidget (pbTabella);
    mainLayout->addWidget (pbAddRiga);
    mainLayout->addWidget (pbRemRiga);
    mainLayout->addWidget (pbSalvaFile);

    setLayout (mainLayout);

    setMaximumHeight (200);
    setMinimumHeight (200);
    setSizePolicy (QSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed));

    tabella = new MyTableView (data);

    setTitle ("Controlli tabella");

    connect (pbTabella, SIGNAL (clicked ()), tabella, SIGNAL (tablePronta ()));
    connect (pbTabella, SIGNAL (clicked ()), this, SLOT (enableTabella ()));
    connect (pbAddRiga, SIGNAL (clicked ()), tabella,
             SIGNAL (richiestaAggiunta ()));
    connect (pbRemRiga, SIGNAL (clicked ()), tabella,
             SIGNAL (richiestaRimossa ()));
    connect (pbSalvaFile, SIGNAL (clicked ()), this,
             SLOT (iniziaSalvataggio ()));
}

void
TableChooser::iniziaSalvataggio ()
{
    QString path = QFileDialog::getSaveFileName (this, tr ("Salva il file"),
                                                 "/home", tr ("JSON (*.json)"));
    if (path != "")
        {
            data->salvaJsonDati (path.append (".json"));
        }
}

MyTableView *
TableChooser::getTabella () const
{
    return tabella;
}

Dati *
TableChooser::getDati () const
{
    return data;
}

void
TableChooser::enableTabella ()
{
    pbAddRiga->setEnabled (true);
    pbRemRiga->setEnabled (true);
}

void
TableChooser::disableTabella ()
{
    pbAddRiga->setEnabled (false);
    pbRemRiga->setEnabled (false);
}
