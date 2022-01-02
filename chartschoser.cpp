#include "chartschoser.h"
#include "chartsviewer.h"

ChartsChoser::ChartsChoser(QWidget* parent) : QMainWindow(parent)
{
    testLab = new QLabel("Scegli il tipo di grafico:");
    bottLinee = new QPushButton("A linee");
    bottArea = new QPushButton("Ad area");
    bottIsto = new QPushButton("Istogramma");
    bottPlot = new QPushButton("Plot");
    bottRadar = new QPushButton("Radar");

    QGridLayout* gridCharts = new QGridLayout;

    resize(250,150);

    testFin = new QWidget();
    testFin->setLayout(gridCharts);

    gridCharts->addWidget(testLab, 0, 0, 1, 2);
    gridCharts->addWidget(bottLinee, 1, 0, 1, 1);
    gridCharts->addWidget(bottArea, 1, 1, 1, 1);
    gridCharts->addWidget(bottIsto, 2, 0, 1, 1);
    gridCharts->addWidget(bottPlot, 2, 1, 1, 1);
    gridCharts->addWidget(bottRadar, 3, 0, 1, 2);

    setCentralWidget(testFin);
}

ChartsChoser::~ChartsChoser(){}
