#include "dataviewer.h"

DataViewer::DataViewer(Dati* d, QWidget *parent) :
    QMainWindow{parent},
    gbControlliTab(new TableChooser(d)),
    gbControlliGraf(new ChartsChooser(gbControlliTab->getDati())),
    tabella(gbControlliTab->getTabella()),
    grafico(gbControlliGraf->getGrafico())
{
    glMain = new QGridLayout();
    hbDescr = new QHBoxLayout();
    hbGraf = new QHBoxLayout();

    gbDescr = new QGroupBox("Descrizione");
    gbMostraDati = new QGroupBox();

    gbControlliTab->setMaximumWidth(gbControlliGraf->width());
    gbControlliTab->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    lbDescr = new QLabel();
    lbDescr->setMaximumWidth(gbControlliGraf->width());
    lbDescr->setWordWrap(true);
    lbDescr->setAlignment(Qt::AlignJustify);
    setDescr(MyChart::GraphType::LineG);
    //lbDescr->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    hbDescr->addWidget(lbDescr);
    gbDescr->setLayout(hbDescr);
    gbDescr->setMaximumWidth(gbControlliGraf->width());
    gbDescr->setMaximumHeight(200);
    gbDescr->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    glMain->addWidget(gbControlliGraf, 0, 0);
    glMain->addWidget(gbControlliTab, 1, 0);
    glMain->addWidget(gbDescr, 2, 0);

    errorDialog = new QErrorMessage();

    setMinimumSize(325,800);
    setMaximumSize(325,800);

    finestra = new QWidget();
    finestra->setLayout(glMain);

    setCentralWidget(finestra);
    setWindowTitle("Visualizzazione dati");
    connect(grafico, SIGNAL(chartPronto()), this, SLOT(mostraChart()));
    connect(grafico, SIGNAL(tipoChartPronto(MyChart::GraphType)), this, SLOT(setDescr(MyChart::GraphType)));
    connect(tabella, SIGNAL(tablePronta()), this, SLOT(mostraTable()));
    connect(gbControlliGraf, SIGNAL(comboChanged(MyChart::GraphType)), this, SLOT(setDescr(MyChart::GraphType)));
    connect(gbControlliGraf, SIGNAL(chartCreated()), gbControlliTab, SLOT(disableTabella()));
    connect(gbControlliGraf, SIGNAL(erroreGraf(QString)), this, SLOT(erroreDialog(QString)));
}

void DataViewer::mostraChart() {
    setMinimumWidth(1000);
    setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    tabella->close();

    if(hbGraf->count()!=1)
        resize(gbControlliGraf->width()+1250, 800);

    hbGraf->removeWidget(tabella);
    hbGraf->addWidget(grafico);

    grafico->show();

    gbMostraDati->setTitle("Grafico");
    gbMostraDati->setLayout(hbGraf);

    glMain->addWidget(new QLabel(),3,0);
    glMain->addWidget(gbMostraDati, 0, 1, 4, 1);
}

void DataViewer::mostraTable() {
    setMinimumWidth(1000);
    setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    grafico->close();

    if(hbGraf->count()!=1)
        resize(gbControlliGraf->width()+1101, 800);

    hbGraf->removeWidget(grafico);
    hbGraf->addWidget(tabella);

    tabella->show();

    gbMostraDati->setTitle("Tabella");
    gbMostraDati->setLayout(hbGraf);

    lbDescr->setText("Visualizzazione dei dati in forma tabellare. È possibile modificare e salvare i dati aggiornati in un file JSON.");

    glMain->addWidget(new QLabel(),3,0);
    glMain->addWidget(gbMostraDati, 0, 1, 4, 1);
}

void DataViewer::setDescr(const MyChart::GraphType& tipoChart) {
    switch(tipoChart) {
        case(MyChart::GraphType::LineG) :
            lbDescr->setText("Dopo aver selezionato almeno un componente, premere il tasto \"Visualizza grafico\". Verrà mostrato un grafico a linee. Il grafico mostra l'andamento dei componenti scelti (o dell'Air Quality Index) nel range di tempo selezionato."); break;
        case(MyChart::GraphType::BarG) :
            lbDescr->setText("Dopo aver selezionato almeno un componente, premere il tasto \"Visualizza grafico\". Verrà mostrato un istogramma. Il range di tempo selezionato è stato suddiviso in 10 parti uguali. Per ogni intervallo viene visualizzata la media dei valori."); break;
        case(MyChart::GraphType::ScatterG) :
            lbDescr->setText("Dopo aver selezionato un componente, premere il tasto \"Visualizza grafico\". Verrà mostrato un plot chart. Viene visualizzata la distribuzione oraria dei valori per ogni giorno all'interno del range di tempo selezionato. È possibile visualizzare dati riguardanti un solo componente per volta."); break;
        case(MyChart::GraphType::AreaG) :
            lbDescr->setText("Dopo aver selezionato almeno un componente, premere il tasto \"Visualizza grafico\". Verrà mostrato un grafico ad aree. Attraverso questo grafico è possibile confrontare tra loro i valori dei vari componenti."); break;
        case(MyChart::GraphType::RadarG) :
            lbDescr->setText("Dopo aver selezionato almeno tre componenti, premere il tasto \"Visualizza grafico\". Verrà mostrato un grafico radar. Il grafico è utile per confrontare valori di ogni componente selezionato nel primo e nell'ultimo giorno del range di tempo scelto con i valori massimi consentiti (fonte: ARPAV)."); break;
        default : lbDescr->setText("nessun grafico");
    }
}

void DataViewer::erroreDialog(const QString& errore) {
    errorDialog->showMessage(errore);
}
