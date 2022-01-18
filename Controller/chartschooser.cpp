#include "chartschooser.h"
#include <QDebug>
#include <QDateTimeAxis>

ChartsChooser::ChartsChooser(const Dati& graf, QWidget* parent) : QMainWindow(parent), data(graf)
{
    testLab = new QLabel("Scegli il tipo di grafico:");
    bottLinee = new QPushButton("A linee");
    bottArea = new QPushButton("Ad area");
    bottIsto = new QPushButton("Istogramma");
    bottPlot = new QPushButton("Plot");
    bottRadar = new QPushButton("Radar");
    grafico = new MyChartView();

    QStringList listaComp = data.getChiavi();
    listaComp.removeFirst();
    componenti = new QComboBox();
    componenti->addItems(listaComp);
    gridCharts = new QGridLayout;

    resize(1000,600);

    testFin = new QWidget();
    testFin->setLayout(gridCharts);

    gridCharts->addWidget(testLab, 0, 0, 1, 2);
    gridCharts->addWidget(bottLinee, 1, 0, 1, 1);
    gridCharts->addWidget(componenti, 1, 1, 1, 1);
    gridCharts->addWidget(bottArea, 2, 0, 1, 1);
    gridCharts->addWidget(bottIsto, 2, 1, 1, 1);
    gridCharts->addWidget(bottPlot, 3, 0, 1, 1);
    gridCharts->addWidget(bottRadar, 3, 1, 1, 1);

    grafico->chart()->setAnimationOptions(QtCharts::QChart::AllAnimations);
    grafico->chart()->setAnimationDuration(5000);

    gridCharts->addWidget(grafico);

    setCentralWidget(testFin);
    connect(bottLinee,SIGNAL(clicked()),this,SLOT(displayLineChart()));
    connect(bottIsto,SIGNAL(clicked()),this,SLOT(displayBarChart()));
}

void ChartsChooser::displayLineChart(){
    grafico->lineChart(data, componenti->currentText());
}

void ChartsChooser::displayBarChart(){
    grafico->barChart(data);
}


