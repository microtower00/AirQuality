#include "chartsviewer.h"

ChartsViewer::ChartsViewer(const Dati& d, QWidget *parent) : QMainWindow{parent}
{
    griglia = new QGridLayout();

    GBcontrolli = new ChartsChooser(d);

    GBdescrizione = new QGroupBox("Descrizione");
    layoutDescr = new QHBoxLayout();
    descrizione = new QTextEdit("ciao");

    GBgrafico = new QGroupBox("Grafico");
    layoutGraf = new QHBoxLayout();

    griglia->addWidget(GBcontrolli, 0, 0);

    setWindowTitle("Grafici");

    finestra = new QWidget();
    finestra->setLayout(griglia);

    setCentralWidget(finestra);

    connect(GBcontrolli->getGrafico(), SIGNAL(chartPronto()), this, SLOT(mostraChart()));
}

void ChartsViewer::mostraChart() {
    layoutGraf->addWidget(GBcontrolli->getGrafico());
    GBgrafico->setLayout(layoutGraf);

    layoutDescr->addWidget(descrizione);
    GBdescrizione->setLayout(layoutDescr);
    GBdescrizione->setMaximumWidth(GBcontrolli->height());
    GBdescrizione->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

    griglia->addWidget(GBgrafico, 0, 1, 2, 1);
    griglia->addWidget(GBdescrizione, 1, 0);

    resize(GBcontrolli->width()+1250,750);
}
