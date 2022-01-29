#include "mychartview.h"
#include <QDebug>

#include <QScatterSeries>
#include <QCategoryAxis>
#include <typeinfo>

using namespace QtCharts;

const int MAXCO = 40000;
const int MAXSO2 = 150;
const int MAXNO = 30;
const int MAXNO2 = 200;
const int MAXO3 = 65;
const int MAXNH3 = 18;
const int MAXPM10 = 50;
const int MAXPM2_5 = 25;

QMap<QString,double> MASSIMICONSENTITI;

MyChartView::MyChartView()
{
    MASSIMICONSENTITI.insert("co",MAXCO);
    MASSIMICONSENTITI.insert("so2",MAXSO2);
    MASSIMICONSENTITI.insert("nh3",MAXNH3);
    MASSIMICONSENTITI.insert("no",MAXNO);
    MASSIMICONSENTITI.insert("no2",MAXNO2);
    MASSIMICONSENTITI.insert("o3",MAXO3);
    MASSIMICONSENTITI.insert("pm10",MAXPM10);
    MASSIMICONSENTITI.insert("pm2_5",MAXPM2_5);
}

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
    QMap<QString, QtCharts::QLineSeries*> serie;

    chart()->setTitle("Andamento di "+comp+" e "+comp2+" nel tempo");

    for(auto itDati:dati) {
        //Stavo provando a fare area per ogni componente, interrotto per mancanza di tempo
        /*for(auto componente : itDati.keys()){
            serie.insert(itDati.value("Data"), itDati.value(componente));
        }*/

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
    QMap<QString,double> mediePrimoGiorno;
    QMap<QString,double> medieUltimoGiorno;

    //prendo la media di tutti i componenti nel primo giorno e nell'ultimo
    QString giornoInizio = QDateTime::fromTime_t(dati.at(0).value("Data")).toString("dd-MM-yyyy");
    QString giornoFine = QDateTime::fromTime_t(dati.at(dati.length()-1).value("Data")).toString("dd-MM-yyyy");

    for(auto record:dati){
        //se é del giorno di inizio, itera e fai media
        if(QDateTime::fromTime_t(record.value("Data")).toString("dd-MM-yyyy")==giornoInizio){
            for(auto componente: record.keys()){
                mediePrimoGiorno.insert(componente, (mediePrimoGiorno.value(componente)+record.value(componente))/2);
            }
        }
        //se é l'ultimo giorno, itera e fai la media
        else if(QDateTime::fromTime_t(record.value("Data")).toString("dd-MM-yyyy")==giornoFine){
            for(auto componente: record.keys()){
                medieUltimoGiorno.insert(componente, (medieUltimoGiorno.value(componente)+record.value(componente))/2);
            }
        }
    }

    QLineSeries *seriesFirstDay = new QLineSeries();
    seriesFirstDay->setName("Giorno iniziale");


    QLineSeries *seriesLastDay = new QLineSeries();
    seriesLastDay->setName("Giorno finale");

    QLineSeries *valRiferimento = new QLineSeries();
    valRiferimento->setName("Valori massimi consentiti");

    mediePrimoGiorno.remove("Data");
    mediePrimoGiorno.remove("aqi");

    medieUltimoGiorno.remove("Data");
    medieUltimoGiorno.remove("aqi");

    int tickN=0;

    //creo una mappa per i fondo scala di ogni componente
    QMap<QString, double> fondoScala;
    for(auto componente:MASSIMICONSENTITI.keys()){
        fondoScala.insert(componente, mediePrimoGiorno.value(componente) > MASSIMICONSENTITI.value(componente) ? std::max(mediePrimoGiorno.value(componente),medieUltimoGiorno.value(componente)) : std::max(MASSIMICONSENTITI.value(componente),medieUltimoGiorno.value(componente)));
    }
    //inserisco i punti
    for(auto componente:MASSIMICONSENTITI.keys()){

        seriesFirstDay->append(QPointF(360/mediePrimoGiorno.values().length()*tickN, mediePrimoGiorno.value(componente)*100/fondoScala.value(componente)));
        valRiferimento->append(QPointF(360/MASSIMICONSENTITI.values().length()*tickN, MASSIMICONSENTITI.value(componente)*100/fondoScala.value(componente)));
        //qDebug()<<360/medieUltimoGiorno.values().length()*tickN;
        //qDebug()<<medieUltimoGiorno.value(componente)*100/fondoScala.value(componente);
        seriesLastDay->append(QPointF(360/medieUltimoGiorno.values().length()*tickN, medieUltimoGiorno.value(componente)*100/fondoScala.value(componente)));
        ++tickN;
    }

    //Chiudo il "cerchio"
    double fondoInizio = fondoScala.values().at(0);
    seriesFirstDay->append(QPointF(360, mediePrimoGiorno.values().at(0)*100/fondoInizio));
    seriesLastDay->append(QPointF(360, medieUltimoGiorno.values().at(0)*100/fondoInizio));
    valRiferimento->append(QPointF(360,MASSIMICONSENTITI.values().at(0)*100/fondoInizio));
    QPolarChart *pChart = new QPolarChart();



    /*QAreaSeries* firstDayArea = new QAreaSeries(seriesFirstDay);
    firstDayArea->setColor(QColor::fromRgba(qRgba(0,255,0,128)));
    firstDayArea->setName("Primo giorno");

    QAreaSeries* lastDayArea = new QAreaSeries(seriesLastDay);
    lastDayArea->setColor(QColor::fromRgba(qRgba(255,0,0,128)));
    lastDayArea->setName("Ultimo giorno");

    QAreaSeries* rifArea = new QAreaSeries(valRiferimento);
    rifArea->setColor(QColor::fromRgba(qRgba(0,0,255,128)));
    rifArea->setName("Valori di riferimento");*/


    pChart->addSeries(seriesFirstDay);
    pChart->addSeries(seriesLastDay);
    pChart->addSeries(valRiferimento);

    //qDebug()<<max;

    //asse radiale
    QValueAxis *ugm3 = new QValueAxis;
    ugm3->setRange(0, 100);
    ugm3->setTickCount(7);
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
    for(int i=0;i<chiavi.length();i++){
        componenti->append(chiavi.at(i),360/chiavi.length()*i);
    }

    seriesFirstDay->attachAxis(componenti);
    seriesFirstDay->attachAxis(ugm3);

    seriesLastDay->attachAxis(componenti);
    seriesLastDay->attachAxis(ugm3);

    valRiferimento->attachAxis(componenti);
    valRiferimento->attachAxis(ugm3);

    this->setChart(pChart);

}

void MyChartView::resetView(){
    QtCharts::QChart* graf = this->chart();
    this->setChart(new QtCharts::QChart());
    delete graf;}
