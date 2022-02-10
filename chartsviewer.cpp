#include "chartsviewer.h"

ChartsViewer::ChartsViewer(const Dati& d, QWidget *parent) :
    QMainWindow{parent},
    gbControlliGraf(new ChartsChooser(d)),
    gbControlliTab(new TableChooser(d)),
    glMain(new QGridLayout()),
    tabella(gbControlliTab->getTabella()),
    grafico(gbControlliGraf->getGrafico())
{
    hbDescr = new QHBoxLayout();
    hbGraf = new QHBoxLayout();

    gbDescr = new QGroupBox("Descrizione");
    gbMostraDati = new QGroupBox();

    gbControlliTab->setMaximumWidth(gbControlliGraf->width());
    gbControlliTab->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    lbDescr = new QLabel();
    lbDescr->setMaximumWidth(gbControlliGraf->width());
    lbDescr->setWordWrap(true);

    hbDescr->addWidget(lbDescr);
    gbDescr->setLayout(hbDescr);
    gbDescr->setMaximumWidth(gbControlliGraf->width());
    gbDescr->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    glMain->addWidget(gbControlliGraf, 0, 0);
    glMain->addWidget(gbControlliTab, 1, 0);

    finestra = new QWidget();
    finestra->setLayout(glMain);

    setCentralWidget(finestra);
    setWindowTitle("Visualizzazione dati");
    //grafico = gbControlliGraf->getGrafico();
    //tabella = gbControlliTab->getTabella();

    connect(grafico, SIGNAL(chartPronto()), this, SLOT(mostraChart()));
    connect(grafico, SIGNAL(tipoChartPronto(MyChart::GraphType)), this, SLOT(setDescr(MyChart::GraphType)));
    connect(tabella, SIGNAL(tablePronta()), this, SLOT(mostraTable()));
}

void ChartsViewer::mostraChart() {
    tabella->close();

    if(hbGraf->count()!=1) {
        resize(gbControlliGraf->width()+1250, 750);
    }

    hbGraf->removeWidget(tabella);
    hbGraf->addWidget(grafico);

    grafico->show();

    gbMostraDati->setTitle("Grafico");
    gbMostraDati->setLayout(hbGraf);

    glMain->addWidget(gbMostraDati, 0, 1, 2, 1);
    glMain->addWidget(gbDescr, 2, 0);
}

void ChartsViewer::mostraTable() {
    grafico->close();

    if(hbGraf->count()!=1) {
        resize(gbControlliGraf->width()+1101, 750);
    }

    hbGraf->removeWidget(grafico);
    hbGraf->addWidget(tabella);

    tabella->show();

    gbMostraDati->setTitle("Tabella");
    gbMostraDati->setLayout(hbGraf);

    lbDescr->setText("Visualizzazione dei dati in forma tabellare. È possibile modificare e salvare i dati aggiornati in un file JSON.");

    glMain->addWidget(gbMostraDati, 0, 1, 2, 1);
    glMain->addWidget(gbDescr, 2, 0);
}

void ChartsViewer::setDescr(const MyChart::GraphType& tipoChart) {
    switch(tipoChart) {
        case(MyChart::GraphType::LineG) :
            lbDescr->setText("Si sta visualizzando un grafico a linee. Il grafico mostra l'andamento dei componenti scelti (o dell'Air Quality Index) nel range di tempo selezionato."); break;
        case(MyChart::GraphType::BarG) :
            lbDescr->setText("Si sta visualizzando un istogramma. Il range di tempo selezionato è stato suddiviso in 10 parti uguali. Per ogni intervallo viene visualizzata la media dei valori."); break;
        case(MyChart::GraphType::ScatterG) :
            lbDescr->setText("Si sta visualizzando un plot chart. Viene visualizzata la distribuzione oraria dei valori per ogni giorno all'interno del range di tempo selezionato. È possibile visualizzare dati riguardanti un solo componente per volta."); break;
        case(MyChart::GraphType::AreaG) :
            lbDescr->setText("Si sta visualizzando un grafico ad aree. Attraverso questo grafico è possibile confrontare tra i valori dei vari componenti."); break;
        case(MyChart::GraphType::RadarG) :
            lbDescr->setText("Si sta visualizzando un grafico radar. Il grafico è utile per confrontare valori di ogni componente selezionato nel primo e nell'ultimo giorno del range di tempo scelto con i valori massimi consentiti (fonte: ARPAV). È necessario selezionare almeno 3 componenti."); break;
        default : lbDescr->setText("nessun grafico");
    }
}
