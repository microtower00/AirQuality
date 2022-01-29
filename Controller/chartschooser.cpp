#include "chartschooser.h"
#include <QDebug>
#include <QDateTimeAxis>
#include <QSizePolicy>

ChartsChooser::ChartsChooser(const Dati& graf, QWidget* parent) : QMainWindow(parent), data(graf)
{
    testLab = new QLabel("Scegli il tipo di grafico:");
    bottLinee = new QPushButton("A linee");
    bottArea = new QPushButton("Ad area");
    bottIsto = new QPushButton("Istogramma");
    bottPlot = new QPushButton("Plot");
    bottRadar = new QPushButton("Radar");
    grafico = new MyChartView();
    //scrollA = new QScrollArea();

    QStringList listaComp = data.getChiavi();
    listaComp.removeFirst();
    componenti = new QComboBox();
    componenti->addItems(listaComp);

    componenti2 = new QComboBox();
    componenti2->addItems(listaComp);
    gridCharts = new QGridLayout;

    resize(1000,600);

    testFin = new QWidget();
    testFin->setLayout(gridCharts);

    gridCharts->addWidget(testLab, 0, 0, 1, 2);
    gridCharts->addWidget(bottLinee, 1, 0, 1, 1);
    gridCharts->addWidget(componenti, 1, 1, 1, 1);
    gridCharts->addWidget(componenti2, 1, 2, 1, 1);
    gridCharts->addWidget(bottArea, 2, 0, 1, 1);
    gridCharts->addWidget(bottIsto, 2, 1, 1, 1);
    gridCharts->addWidget(bottPlot, 3, 0, 1, 1);
    gridCharts->addWidget(bottRadar, 3, 1, 1, 1);

    grafico->chart()->setAnimationOptions(QtCharts::QChart::AllAnimations);
    grafico->chart()->setAnimationDuration(5000);

    // abbandono momentaneamente l'idea di rendere scrollabili grafici perchè
    // gestire sta cosa mi fa bestemmiare
    /*grafico->setMinimumSize(1000,800);
    qDebug()<<grafico->sizeHint();
    grafico->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    //grafico->setMaximumSize(1000000,800);
    scrollA->setWidget(grafico);
    gridCharts->addWidget(scrollA);*/

    gridCharts->addWidget(grafico);

    setCentralWidget(testFin);
    connect(bottLinee,SIGNAL(clicked()),this,SLOT(displayLineChart()));
    connect(bottIsto,SIGNAL(clicked()),this,SLOT(displayBarChart()));
    connect(bottRadar,SIGNAL(clicked()),this,SLOT(displayRadarChart()));
    connect(bottArea,SIGNAL(clicked()),this,SLOT(displayAreaChart()));
}

void ChartsChooser::displayLineChart(){
    grafico->lineChart(data, componenti->currentText());
}

void ChartsChooser::displayBarChart(){
    grafico->barChart(data);
}

void ChartsChooser::displayRadarChart(){
    grafico->radarChart(data);
}

void ChartsChooser::displayAreaChart(){
    qDebug()<<"te voi ca te odia";
    grafico->areaChart(data, componenti->currentText(), componenti2->currentText());
}


