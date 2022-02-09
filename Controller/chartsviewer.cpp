#include "chartsviewer.h"

ChartsViewer::ChartsViewer(const Dati& d, QWidget *parent) : QMainWindow{parent}
{

    griglia = new QGridLayout();
    layoutDescr = new QHBoxLayout();
    layoutGraf = new QHBoxLayout();

    GBcontrolliG = new ChartsChooser(d);
    GBcontrolliT = new TableChooser(d);
    GBdescrizione = new QGroupBox("Descrizione");
    GBmostraDati = new QGroupBox();

    GBcontrolliT->setMaximumWidth(GBcontrolliG->width());
    GBcontrolliT->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    descrizione = new QLabel();
    descrizione->setMaximumWidth(GBcontrolliG->width());
    descrizione->setWordWrap(true);

    layoutDescr->addWidget(descrizione);
    GBdescrizione->setLayout(layoutDescr);
    GBdescrizione->setMaximumWidth(GBcontrolliG->width());
    GBdescrizione->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    griglia->addWidget(GBcontrolliG, 0, 0);
    griglia->addWidget(GBcontrolliT, 1, 0);

    finestra = new QWidget();
    finestra->setLayout(griglia);

    setCentralWidget(finestra);
    setWindowTitle("Visualizzazione dati");

    grafico = GBcontrolliG->getGrafico();
    tabella = GBcontrolliT->getTabella();

    connect(grafico, SIGNAL(chartPronto()), this, SLOT(mostraChart()));
    connect(grafico, SIGNAL(tipoChartPronto(MyChart::GraphType)), this, SLOT(setDescr(MyChart::GraphType)));
    connect(tabella, SIGNAL(tablePronta()), this, SLOT(mostraTable()));
}

void ChartsViewer::mostraChart() {
    tabella->close();

    if(layoutGraf->count()!=1) {
        resize(GBcontrolliG->width()+1250, 750);
    }

    layoutGraf->removeWidget(tabella);
    layoutGraf->addWidget(grafico);

    grafico->show();

    GBmostraDati->setTitle("Grafico");
    GBmostraDati->setLayout(layoutGraf);

    griglia->addWidget(GBmostraDati, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 2, 0);
}

void ChartsViewer::mostraTable() {
    grafico->close();

    if(layoutGraf->count()!=1) {
        resize(GBcontrolliG->width()+1101, 750);
    }

    layoutGraf->removeWidget(grafico);
    layoutGraf->addWidget(tabella);

    tabella->show();

    GBmostraDati->setTitle("Tabella");
    GBmostraDati->setLayout(layoutGraf);

    descrizione->setText("Visualizzazione dei dati in forma tabellare. È possibile modificare e salvare i dati aggiornati in un file JSON.");

    griglia->addWidget(GBmostraDati, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 2, 0);
}

void ChartsViewer::setDescr(const MyChart::GraphType& tipoChart) {
    switch(tipoChart) {
        case(MyChart::GraphType::LineG) :
            descrizione->setText("Si sta visualizzando un grafico a linee. Il grafico mostra l'andamento dei componenti scelti (o dell'Air Quality Index) nel range di tempo selezionato."); break;
        case(MyChart::GraphType::BarG) :
            descrizione->setText("Si sta visualizzando un istogramma. Il range di tempo selezionato è stato suddiviso in 10 parti uguali. Per ogni intervallo viene visualizzata la media dei valori."); break;
        case(MyChart::GraphType::ScatterG) :
            descrizione->setText("Si sta visualizzando un plot chart. Viene visualizzata la distribuzione oraria dei valori per ogni giorno all'interno del range di tempo selezionato. È possibile visualizzare dati riguardanti un solo componente per volta."); break;
        case(MyChart::GraphType::AreaG) :
            descrizione->setText("Si sta visualizzando un grafico ad aree. Attraverso questo grafico è possibile confrontare tra i valori dei vari componenti."); break;
        case(MyChart::GraphType::RadarG) :
            descrizione->setText("Si sta visualizzando un grafico radar. Il grafico è utile per confrontare valori di ogni componente selezionato nel primo e nell'ultimo giorno del range di tempo scelto con i valori massimi consentiti (fonte: ARPAV). È necessario selezionare almeno 3 componenti."); break;
        default : descrizione->setText("nessun grafico");
    }
}
