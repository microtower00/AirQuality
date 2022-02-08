#include "chartsviewer.h"

ChartsViewer::ChartsViewer(const Dati& d, QWidget *parent) : QMainWindow{parent}
{
    griglia = new QGridLayout();
    layoutDescr = new QHBoxLayout();
    layoutGraf = new QHBoxLayout();

    GBcontrolli = new ChartsChooser(d);
    GBdescrizione = new QGroupBox("Descrizione");
    GBgrafico = new QGroupBox();

    descrizione = new QTextEdit("ciao");

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

    griglia->addWidget(GBgrafico, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 1, 0);
}
