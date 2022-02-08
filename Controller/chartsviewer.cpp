#include "chartsviewer.h"

ChartsViewer::ChartsViewer(const Dati& d, QWidget *parent) : QMainWindow{parent}
{
    griglia = new QGridLayout();
    layoutDescr = new QHBoxLayout();
    layoutGraf = new QHBoxLayout();

    GBcontrolli = new ChartsChooser(d);
    GBdescrizione = new QGroupBox("Descrizione");
    GBgrafico = new QGroupBox();

    descrizione = new QLabel();
    descrizione->setMaximumWidth(GBcontrolli->width());
    descrizione->setWordWrap(true);

    layoutDescr->addWidget(descrizione);
    GBdescrizione->setLayout(layoutDescr);
    GBdescrizione->setMaximumWidth(GBcontrolli->width());
    GBdescrizione->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    griglia->addWidget(GBcontrolli, 0, 0);

    finestra = new QWidget();
    finestra->setLayout(griglia);

    setCentralWidget(finestra);
    setWindowTitle("Grafici");

    grafico = GBcontrolli->getGrafico();
    tabella = GBcontrolli->getTabella();

    connect(grafico, SIGNAL(chartPronto()), this, SLOT(mostraChart()));
    connect(grafico, SIGNAL(tipoChartPronto(MyChart::GraphType)), this, SLOT(setDescr(MyChart::GraphType)));
    connect(tabella, SIGNAL(tablePronta()), this, SLOT(mostraTable()));
}

void ChartsViewer::mostraChart() {
    tabella->close();

    if(layoutGraf->count()!=1) {
        resize(GBcontrolli->width()+1250, 750);
    }

    layoutGraf->removeWidget(tabella);
    layoutGraf->addWidget(grafico);

    grafico->show();

    GBgrafico->setTitle("Grafico");
    GBgrafico->setLayout(layoutGraf);

    griglia->addWidget(GBgrafico, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 1, 0);
}

void ChartsViewer::mostraTable() {
    grafico->close();

    if(layoutGraf->count()!=1) {
        resize(GBcontrolli->width()+1101, 750);
    }

    layoutGraf->removeWidget(grafico);
    layoutGraf->addWidget(tabella);

    tabella->show();

    /*prova header qua ma non va
    tabella->horizontalHeader()->show();
    qDebug()<<tabella->horizontalHeader()->count();
    //tabella->horizontalHeader()->setVisible(true);
    tabella->verticalHeader()->setVisible(true);*/

    GBgrafico->setTitle("Tabella");
    GBgrafico->setLayout(layoutGraf);

    descrizione->setText("Visualizzazione dei dati in forma tabellare. È possibile modificare e salvare i dati aggiornati in un fil JSON.");

    griglia->addWidget(GBgrafico, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 1, 0);
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


