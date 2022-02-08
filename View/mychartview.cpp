#include "mychartview.h"

using namespace QtCharts;

const int MAXCO = 40000;
const int MAXSO2 = 150;
const int MAXNO = 30;
const int MAXNO2 = 200;
const int MAXO3 = 65;
const int MAXNH3 = 18;
const int MAXPM10 = 50;
const int MAXPM2_5 = 25;


MyChartView::MyChartView(const Dati& d) : data(d)
{
    MASSIMICONSENTITI.insert("co",MAXCO);
    MASSIMICONSENTITI.insert("so2",MAXSO2);
    MASSIMICONSENTITI.insert("nh3",MAXNH3);
    MASSIMICONSENTITI.insert("no",MAXNO);
    MASSIMICONSENTITI.insert("no2",MAXNO2);
    MASSIMICONSENTITI.insert("o3",MAXO3);
    MASSIMICONSENTITI.insert("pm10",MAXPM10);
    MASSIMICONSENTITI.insert("pm2_5",MAXPM2_5);

    this->setRenderHint(QPainter::Antialiasing);
}

void MyChartView::setCompScelti(const QStringList& compScelti) {
    comp = compScelti;
    //resize(1250,750);
}

QMap<QString, QtCharts::QLineSeries*> MyChartView::genericLAchart() {}

void MyChartView::lineChart(){
    resetView();
    emit chartPronto();
    QMap<QString, QtCharts::QAbstractSeries*> series;
    //Creo la lineSeries per ogni componente
    for(QString chiave : comp){
        series.insert(chiave, new MyLineSeries(data,chiave));
    }

    this->setChart(new MyChart(series,MyChart::GraphType::LineG));
}

void MyChartView::areaChart(){
    resetView();
    emit chartPronto();
    QMap<QString, QtCharts::QAbstractSeries*> series;
    //Creo la lineSeries per ogni componente
    for(QString chiave : comp){
        series.insert(chiave, new MyLineSeries(data,chiave));
    }

    this->setChart(new MyChart(series,MyChart::GraphType::AreaG));
}

void MyChartView::barChart(){
    resetView();
    emit chartPronto();
    QList<QMap<QString, double>> dati = data.getDati();

    MyBarSeries *serie = new MyBarSeries(data, comp);
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

void MyChartView::radarChart(){
    resetView();
    emit chartPronto();

    QMap<QString,QAbstractSeries*> series;
    QList<QMap<QString,double>> datiElab, datiGrezzi = data.getDati();
    QList<QMap<QString,double>> datiFirstDay, datiLastDay;
    QMap<QString,double> mediaFirstDay, mediaLastDay;

    datiElab.push_back(MASSIMICONSENTITI);
    //Per ogni record, determino se è del primo o ultimo giorno e lo inserisco acco
    for(auto record : datiGrezzi){
        if(record.value("Data")==datiGrezzi.first().value("Data"))
            datiFirstDay.push_back(record);
        if(record.value("Data")==datiGrezzi.last().value("Data"))
            datiLastDay.push_back(record);
    }

    //calcolo le medie
    for(auto record : datiFirstDay){
        for(QString componente : comp){
            mediaFirstDay.insert(componente, mediaFirstDay.value(componente)+record.value(componente)/2);
        }
    }

    for(auto record : datiLastDay){
        for(QString componente : comp){
            mediaLastDay.insert(componente, mediaLastDay.value(componente)+record.value(componente)/2);
        }
    }

    datiElab.push_back(mediaFirstDay);
    datiElab.push_back(mediaLastDay);

    //Creo le serie
    QMap<QString,double> fondoScala = MyPolarSeries::calcolaFondoScala(datiElab);
    qDebug()<<fondoScala;
    qDebug()<<MASSIMICONSENTITI;
    qDebug()<<mediaFirstDay;
    qDebug()<<mediaLastDay;
    QString nomeserie;
    for(QMap<QString,double> entry : datiElab){
        nomeserie = entry == mediaFirstDay ? "Primo giorno" : entry == mediaLastDay ? "Ultimo giorno" : "Val. di riferimento";
        qDebug()<<nomeserie;
        series.insert(nomeserie, new MyPolarSeries(entry, fondoScala, comp));
    }

    MyPolarChart* pChart = new MyPolarChart(series);
    QtCharts::QCategoryAxis* componenti =dynamic_cast<QCategoryAxis*>(pChart->axes(QtCharts::QPolarChart::PolarOrientationAngular).at(0));

    for(int i=0;i<comp.size();i++){
            componenti->append(comp.at(i),360/comp.size()*i);
    }

    this->setChart(pChart);

}

void MyChartView::scatterChart() {
    resetView();
    emit chartPronto();
    //MyChartView::show();
    QString singleComp = comp.first();

    MyScatterSerie* sSerie = new MyScatterSerie(data, singleComp);
    sSerie->setMarkerSize(10);
    sSerie->setName(singleComp);

    //mi pare strano
    QMap<QString, QAbstractSeries*> param;
    param.insert(singleComp, sSerie);
    setChart(new MyChart(param, MyChart::GraphType::ScatterG));

}

void MyChartView::resetView(){
    QtCharts::QChart* graf = this->chart();
    this->setChart(new QtCharts::QChart());
    delete graf;
    resize(1250,750);
}

QLineSeries* MyChartView::sommaY(QLineSeries *upper, QLineSeries *lower) const {
    QVector<QPointF> puntiLower = lower->pointsVector();
    QVector<QPointF> puntiUpper = upper->pointsVector();

    for(int i=0;i<puntiLower.size();++i){
        puntiUpper[i].setY(puntiLower.at(i).y()+puntiUpper.at(i).y());
    }
    upper->replace(puntiUpper);
    return upper;
}

double MyChartView::maxValueFromListSeries(QList<QtCharts::QLineSeries*> series) {
    double max=0;

    for(auto serie:series) {
        if(maxFromSerie(serie)>max)
            max=maxFromSerie(serie);
    }

    return max;
}

double MyChartView::maxFromSerie(QtCharts::QXYSeries* serie) {
    double max=0;

    for(unsigned int i=0; i<serie->count(); ++i) {
        if(serie->at(i).y()>max) {
            max = serie->at(i).y();
        }
    }

    return max;
}
