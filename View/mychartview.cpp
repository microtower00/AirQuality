#include "mychartview.h"
#include <QDebug>

MyChartView::MyChartView()
{}

void MyChartView::lineChart(const Dati& data, QString comp){
    resetView();
    QtCharts::QLineSeries* serieCo = new QtCharts::QLineSeries();

    QList<QMap<QString, double>> dati = data.getDati();

    chart()->setTitle("Andamento del "+comp+" nel tempo");

    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        serieCo->append(QPointF(data.getDateFromDouble(itDati->value("Data")).toMSecsSinceEpoch(),itDati->value(comp)));
        //qDebug() << data.getDateFromDouble(itDati->value("Data"));
        //qDebug()<<serieCo->at(std::distance(dati.begin(),itDati));
    }

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

void MyChartView::barChart(const Dati & data){
    resetView();
    QList<QString> chiavi = data.getChiavi();
    qDebug()<<chiavi;
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

    this->chart()->addSeries(serie);
    QtCharts::QBarCategoryAxis* asse = new QtCharts::QBarCategoryAxis();

    for(auto itDati = dati.begin(); itDati!=dati.end(); ++itDati) {
        asse->append(data.getDateFromDouble(itDati->value("Data"))  .toString(Qt::ISODate));
    }
    asse->setRange(QDateTime::currentDateTime().addMonths(-1).toString(),QDateTime::currentDateTime().toString());
    this->chart()->createDefaultAxes();
    this->chart()->setAxisX(asse, serie);

    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::resetView(){
    QtCharts::QChart* graf = this->chart();
    this->setChart(new QtCharts::QChart());
    delete graf;}
