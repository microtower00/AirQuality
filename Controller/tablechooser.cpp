#include "tablechooser.h"

TableChooser::TableChooser(const Dati& dati) :  data(dati)
{
    mainLayout = new QVBoxLayout();

    pbTabella = new QPushButton("Visualizza tabella con tutti i dati");
    pbAddRiga = new QPushButton("Aggiungi una riga");
    pbSalvaFile = new QPushButton("Salva i dati correnti");

    mainLayout->addWidget(pbTabella);
    mainLayout->addWidget(pbAddRiga);
    mainLayout->addWidget(pbSalvaFile);

    setLayout(mainLayout);

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    tabella = new MyTableView(data);

    setTitle("Controlli tabella");

    connect(pbTabella,SIGNAL(clicked()),tabella,SIGNAL(tablePronta()));
    connect(pbAddRiga, SIGNAL(clicked()), tabella, SIGNAL(richiestaAggiunta()));
    connect(pbSalvaFile,SIGNAL(clicked()),this,SLOT(iniziaSalvataggio()));
}

void TableChooser::iniziaSalvataggio(){
    QString path = QFileDialog::getSaveFileName(this, tr("Salva il file"),"/home",tr("JSON (*.json)"));
    if(path!=""){
        data.salvaJsonDati(path.append(".json"));
    }
}

MyTableView* TableChooser::getTabella() const {
    return tabella;
}
