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
    grafico = new QtCharts::QChartView();

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

    grafico->chart()->setAnimationOptions(QtCharts::QChart::AllAnimations);
    grafico->chart()->setAnimationDuration(5000);

    gridCharts->addWidget(grafico);

    setCentralWidget(testFin);
    connect(bottLinee,SIGNAL(clicked()),this,SLOT(createLineChart()));
    connect(bottIsto,SIGNAL(clicked()),this,SLOT(createBarChart()));
}

void ChartsChooser::createLineChart(){
    QtCharts::QLineSeries* serieCo = new QtCharts::QLineSeries();

    QList<QMap<QString, double>> dati = data.getDati();

    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        //qDebug()<<"Aggiungo punto in coords: "+QString::number(itDati->value("Data"))+", "+QString::number(itDati->value("co"));
        serieCo->append(QPointF(data.getDateFromDouble(itDati->value("Data")).toMSecsSinceEpoch(),itDati->value("co")));
        //qDebug() << data.getDateFromDouble(itDati->value("Data"));
        //qDebug()<<serieCo->at(std::distance(dati.begin(),itDati));
    }

    //QtCharts::QChart* graph = new QtCharts::QChart();
    grafico->chart()->addSeries(serieCo);

    QtCharts::QDateTimeAxis* asseX = new QtCharts::QDateTimeAxis;
    asseX->setFormat("dd-MM-yyyy h:mm");
    asseX->setTickCount(12);

    grafico->chart()->setAxisX(asseX, serieCo);
}

void ChartsChooser::createBarChart(){
    QList<QString> chiavi = data.getChiavi();
    //tolgo data, aqi e co2 (fuori scala)
    chiavi.removeFirst();
    chiavi.removeLast();
    chiavi.removeFirst();

    // tutto ciò che è stato fatto qua sotto è spiegato abbastanza bene nella doc di QBarSeries (barChartExample) (sicuramente spiegato meglio di quanto potrei fare io che sono cotto)
    QList<QtCharts::QBarSet*> componenti;
    for(auto it=chiavi.begin(); it!=chiavi.end(); ++it)
        componenti.push_back(new QtCharts::QBarSet(*it));

    QList<QMap<QString, double>> dati = data.getDati();

    QtCharts::QBarSeries *serie = new QtCharts::QBarSeries();

    for(auto it=chiavi.begin(); it!=chiavi.end(); ++it) {
        for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
            *componenti[(std::distance(chiavi.begin(), it))]<< itDati->value(*it);
            serie->append(componenti[(std::distance(chiavi.begin(), it))]);
        }
    }

    grafico->chart()->addSeries(serie);
    QtCharts::QBarCategoryAxis* asse = new QtCharts::QBarCategoryAxis();

    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        asse->append(data.getDateFromDouble(itDati->value("Data")).toString(Qt::ISODate));
    }

    grafico->chart()->createDefaultAxes();
    grafico->chart()->setAxisX(asse, serie);

    grafico->chart()->legend()->setVisible(true);
    grafico->chart()->legend()->setAlignment(Qt::AlignBottom);
}

