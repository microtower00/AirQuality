#include "chartsviewer.h"

ChartsViewer::ChartsViewer(const Dati& d, QWidget *parent) : QMainWindow{parent}
{
    griglia = new QGridLayout();

    GBcontrolli = new ChartsChooser(d);

    GBdescrizione = new QGroupBox("Descrizione");
    layoutDescr = new QHBoxLayout();
    descrizione = new QTextEdit("ciao");

    GBgrafico = new QGroupBox();
    layoutGraf = new QHBoxLayout();

    griglia->addWidget(GBcontrolli, 0, 0);

    setWindowTitle("Grafici");

    finestra = new QWidget();
    finestra->setLayout(griglia);

    setCentralWidget(finestra);

    grafico = GBcontrolli->getGrafico();
    tabella = GBcontrolli->getTabella();

    connect(grafico, SIGNAL(chartPronto()), this, SLOT(mostraChart()));
    connect(tabella, SIGNAL(tablePronta()), this, SLOT(mostraTable()));
}

void ChartsViewer::mostraChart() {
    tabella->close();
    layoutGraf->removeWidget(tabella);

    layoutGraf->addWidget(grafico);
    GBgrafico->setTitle("Grafico");
    GBgrafico->setLayout(layoutGraf);

    layoutDescr->addWidget(descrizione);
    GBdescrizione->setLayout(layoutDescr);
    GBdescrizione->setMaximumWidth(GBcontrolli->width());
    GBdescrizione->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    griglia->addWidget(GBgrafico, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 1, 0);

    resize(GBcontrolli->width()+grafico->width(),750);
}

void ChartsViewer::mostraTable() {
    grafico->close();
    layoutGraf->removeWidget(grafico);

    layoutGraf->addWidget(tabella);
    GBgrafico->setTitle("Tabella");
    GBgrafico->setLayout(layoutGraf);

    layoutDescr->addWidget(descrizione);
    GBdescrizione->setLayout(layoutDescr);
    GBdescrizione->setMaximumWidth(GBcontrolli->width());
    GBdescrizione->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    griglia->addWidget(GBgrafico, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 1, 0);

    resize(GBcontrolli->width()+1101,750);
}
