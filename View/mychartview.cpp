#include "mychartview.h"
#include <QDebug>

#include <QScatterSeries>
#include <QCategoryAxis>
#include <typeinfo>
#define MAX_ELEVATION 90

using namespace QtCharts;


MyChartView::MyChartView()
{}

void MyChartView::lineChart(const Dati& data, QString comp){
    resetView();
    QtCharts::QLineSeries* serieCo = new QtCharts::QLineSeries();

    QList<QMap<QString, double>> dati = data.getDati();

    chart()->setTitle("Andamento del "+comp+" nel tempo");

    for(auto itDati:dati)
        serieCo->append(QPointF(data.getDateFromDouble(itDati.value("Data")).toMSecsSinceEpoch(),itDati.value(comp)));

    //QtCharts::QChart* graph = new QtCharts::QChart();
    this->chart()->addSeries(serieCo);

    QtCharts::QDateTimeAxis* asseX = new QtCharts::QDateTimeAxis;
    asseX->setFormat("dd-MM-yyyy h:mm");
    asseX->setTickCount(12);

    this->chart()->addAxis(asseX, Qt::AlignBottom);
    serieCo->attachAxis(asseX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    this->chart()->addAxis(axisY, Qt::AlignLeft);
    serieCo->attachAxis(axisY);

    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::areaChart(const Dati& data, QString comp, QString comp2){
    resetView();
    QtCharts::QLineSeries* serieComp = new QtCharts::QLineSeries();
    QtCharts::QLineSeries* serieComp2 = new QtCharts::QLineSeries();

    QList<QMap<QString, double>> dati = data.getDati();

    chart()->setTitle("Andamento di "+comp+" e "+comp2+" nel tempo");

    for(auto itDati:dati) {
        serieComp->append(QPointF(data.getDateFromDouble(itDati.value("Data")).toMSecsSinceEpoch(),itDati.value(comp)));
        serieComp2->append(QPointF(data.getDateFromDouble(itDati.value("Data")).toMSecsSinceEpoch(),itDati.value(comp2)));
    }

    //QtCharts::QChart* graph = new QtCharts::QChart();

    QAreaSeries *series = new QAreaSeries(serieComp, serieComp2);
    series->setName("Componenti a confronto");
    this->chart()->addSeries(series);

    QtCharts::QDateTimeAxis* asseX = new QtCharts::QDateTimeAxis;
    asseX->setFormat("dd-MM-yyyy h:mm");
    asseX->setTickCount(12);

    this->chart()->addAxis(asseX, Qt::AlignBottom);
    //serieComp->attachAxis(asseX);

    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    this->chart()->addAxis(axisY, Qt::AlignLeft);
    //serieComp->attachAxis(axisY);

    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::barChart(const Dati & data){
    resetView();
    QList<QString> chiavi = data.getChiavi();
    //qDebug()<<chiavi;
    //tolgo data, aqi e co2 (fuori scala)
    chiavi.removeFirst();
    chiavi.removeLast();
    chiavi.removeFirst();

    // tutto ciò che è stato fatto qua sotto è spiegato abbastanza bene nella doc di QBarSeries (barChartExample) (sicuramente spiegato meglio di quanto potrei fare io che sono cotto)
    QList<QtCharts::QBarSet*> componenti;
    for(auto it:chiavi)
        componenti.push_back(new QtCharts::QBarSet(it));

    QList<QMap<QString, double>> dati = data.getDati();

    QtCharts::QBarSeries *serie = new QtCharts::QBarSeries();

    for(auto it=chiavi.begin(); it!=chiavi.end(); ++it) {
        for(auto itDati:dati) {
            *componenti[(std::distance(chiavi.begin(), it))]<< itDati.value(*it);
            serie->append(componenti[(std::distance(chiavi.begin(), it))]);
        }
    }

    this->chart()->addSeries(serie);
    QtCharts::QBarCategoryAxis* asse = new QtCharts::QBarCategoryAxis();

    for(auto itDati:dati) {
        asse->append(data.getDateFromDouble(itDati.value("Data")).toString(Qt::ISODate));
    }
    asse->setRange(QDateTime::currentDateTime().addMonths(-1).toString(),QDateTime::currentDateTime().toString());
    this->chart()->createDefaultAxes();
    this->chart()->setAxisX(asse, serie);

    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::radarChart(const Dati & data){

    resetView();
    QList<QMap<QString, double>> dati = data.getDati();

    //recupero dati primo giorno
    QLineSeries *seriesFirstDay = new QLineSeries();
    seriesFirstDay->setName("Giorno iniziale");

    QMap<QString, double> datiFirstDay = *dati.begin();
    datiFirstDay.remove("Data");
    datiFirstDay.remove("aqi");
    datiFirstDay.remove("co");

    for(auto it=datiFirstDay.begin(); it!=datiFirstDay.end(); ++it)
        seriesFirstDay->append(QPointF(360/datiFirstDay.values().length()*std::distance(datiFirstDay.begin(), it), it.value()));

    //seriesFirstDay->append(QPointF(0, datiFirstDay.begin().value()));

    //recupero dati ultimo giorno, ridondante
    QLineSeries *seriesLastDay = new QLineSeries();
    seriesLastDay->setName("Giorno finale");

    QMap<QString, double> datiLastDay = *(dati.end()-2);
    datiLastDay.remove("Data");
    datiLastDay.remove("aqi");
    datiLastDay.remove("co");

    for(auto it=datiLastDay.begin(); it!=datiLastDay.end(); ++it)
        seriesLastDay->append(QPointF(360/datiLastDay.values().length()*std::distance(datiLastDay.begin(), it), it.value()));

    //seriesLastDay->append(QPointF(0, datiLastDay.begin().value()));

    QPolarChart *pChart = new QPolarChart();
    pChart->addSeries(seriesFirstDay);
    pChart->addSeries(seriesLastDay);

    double max=0;

    double maxPrimo = *std::max_element(datiFirstDay.begin(), (datiFirstDay.end()));
    double maxUltimo = *std::max_element(datiLastDay.begin(), (datiLastDay.end()));
    maxPrimo>maxUltimo ? max=maxPrimo : max=maxUltimo;

    //qDebug()<<max;

    //asse radiale
    QValueAxis *ugm3 = new QValueAxis;
    ugm3->setRange(0, max);
    ugm3->setTickCount(6);
    ugm3->setLabelsVisible(false);
    pChart->addAxis(ugm3, QPolarChart::PolarOrientationRadial);

    // asse azimutale
    QCategoryAxis *componenti = new QCategoryAxis();
    componenti->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    componenti->setRange(0, 360);
    componenti->setLabelsVisible(true);
    pChart->addAxis(componenti, QPolarChart::PolarOrientationAngular);

    QStringList chiavi = data.getChiavi();
    chiavi.removeFirst();
    chiavi.removeLast();
    chiavi.removeFirst();
    for(int i=0;i<chiavi.length();i++){
        componenti->append(chiavi.at(i),360/chiavi.length()*i);
    }

    seriesFirstDay->attachAxis(componenti);
    seriesFirstDay->attachAxis(ugm3);
    seriesLastDay->attachAxis(componenti);
    seriesLastDay->attachAxis(ugm3);

    //QChartView *chartView = new QChartView(pChart);

    qDebug("Sa incorto che so grosso");
    this->setChart(pChart);

}

void MyChartView::resetView(){
    QtCharts::QChart* graf = this->chart();
    this->setChart(new QtCharts::QChart());
    delete graf;}
