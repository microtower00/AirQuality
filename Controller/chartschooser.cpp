#include "chartschooser.h"
#include <QDebug>

ChartsChooser::ChartsChooser(const Dati& graf, QWidget* parent) : QMainWindow(parent), data(graf)
{
    testLab = new QLabel("Scegli il tipo di grafico:");
    bottLinee = new QPushButton("A linee");
    bottArea = new QPushButton("Ad area");
    bottIsto = new QPushButton("Istogramma");
    bottPlot = new QPushButton("Plot");
    bottRadar = new QPushButton("Radar");

    gridCharts = new QGridLayout;

    resize(250,150);

    testFin = new QWidget();
    testFin->setLayout(gridCharts);

    gridCharts->addWidget(testLab, 0, 0, 1, 2);
    gridCharts->addWidget(bottLinee, 1, 0, 1, 1);
    gridCharts->addWidget(bottArea, 1, 1, 1, 1);
    gridCharts->addWidget(bottIsto, 2, 0, 1, 1);
    gridCharts->addWidget(bottPlot, 2, 1, 1, 1);
    gridCharts->addWidget(bottRadar, 3, 0, 1, 2);

    gridCharts->addWidget(&grafico);



    setCentralWidget(testFin);
    connect(bottLinee,SIGNAL(clicked()),this,SLOT(graficalo()));
}

void ChartsChooser::graficalo(){
    QtCharts::QLineSeries* serie = new QtCharts::QLineSeries();

    QList<QString> chiavi = data.getChiavi();
    QList<QMap<QString, double>> dati = data.getDati();
    /*for (auto it :chiavi ) {
        qDebug()<<it;
    }*/
    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        qDebug()<<"Aggiungo punto in coords: "+QString::number(itDati->value("Data"))+", "+QString::number(itDati->value("co"));
        *serie<<QPointF(itDati->value("Data"),itDati->value("no3"));
    }
    QtCharts::QChart* graph = new QtCharts::QChart();
    graph->addSeries(serie);
    grafico.setChart(graph);
}

