#include "mychart.h"

MyChart::MyChart(QMap<QString,QtCharts::QAbstractSeries*> serie, MyChart::GraphType gt)
{
    switch(gt){
    case MyChart::GraphType::LineG :
        buildLineChart(serie);break;
    case MyChart::GraphType::AreaG :
        buildAreaChart(serie);break;
    case MyChart::GraphType::ScatterG :
        buildScatterChart(serie);break;
    case MyChart::GraphType::PolarG :
        buildPolarChart(serie);break;
    case MyChart::GraphType::BarG :
        buildBarChart(serie);break;
    }

}

void MyChart::buildLineChart(QMap<QString, QtCharts::QAbstractSeries*> serie){
    //asse X
    QtCharts::QDateTimeAxis* asseX = new QtCharts::QDateTimeAxis;
    asseX->setFormat("dd-MM-yyyy h:mm");
    asseX->setTickCount(12);
    addAxis(asseX, Qt::AlignBottom);

    // asse Y
    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    addAxis(asseY, Qt::AlignLeft);

    //Per ogni serie nella mapps setto nome e collego gli assi
    for(auto it=serie.begin(); it!=serie.end(); ++it){
        addSeries(*it);
        it.value()->setName(it.key());
        it.value()->attachAxis(asseX);
        it.value()->attachAxis(asseY);
    }

    //setto il massimo di Y al massimo valore tra tutte le serie
    asseY->setMin(0);
    asseY->setMax(maxValueFromListSeries(serie.values()));
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignBottom);
}

void MyChart::buildAreaChart(QMap<QString, QtCharts::QAbstractSeries *> series){
    //asse X codice riciclabile
    QtCharts::QDateTimeAxis* asseX = new QtCharts::QDateTimeAxis;
    asseX->setFormat("dd-MM-yyyy h:mm");
    asseX->setTickCount(12);
    addAxis(asseX, Qt::AlignBottom);

    // asse Y
    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    addAxis(asseY, Qt::AlignLeft);

    //per ogni serie nella mappa assegno il nome del componente e i relativi assi
    //bonus: creo una QAreaSeries tra la lineseries corrente e la precedente
    QtCharts::QAreaSeries *aSeries;
    QtCharts::QLineSeries* lowerSerie;
    for(auto it=series.begin(); it!=series.end(); ++it){
        lowerSerie = it!=series.begin() ? dynamic_cast<QtCharts::QLineSeries*>(*(it-1)) : Q_NULLPTR;
        aSeries = new QtCharts::QAreaSeries(sommaY(dynamic_cast<QtCharts::QLineSeries*>(*it),lowerSerie),lowerSerie);
        addSeries(aSeries);
        aSeries->setName(it.key());
        aSeries->attachAxis(asseX);
        aSeries->attachAxis(asseY);
    }

    //setto il massimo di Y al massimo valore tra tutte le serie
    asseY->setMin(0);
    asseY->setMax(maxValueFromListSeries(series.values()));
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignBottom);
}
void MyChart::buildScatterChart(QMap<QString, QtCharts::QAbstractSeries*> serie){}

void MyChart::buildPolarChart(QMap<QString, QtCharts::QAbstractSeries*> serie){
    //Per ogni serie setto il nome, e aggiungo al grafico
    for(auto chiave : serie.keys()){
        addSeries(serie.value(chiave));
        serie.value(chiave)->setName(chiave);
    }

    QtCharts::QValueAxis *ugm3 = new QtCharts::QValueAxis;
    ugm3->setRange(0, 100);
    //Setto il numero di ticks uguale al numero di punti in una serie (Cioè il numero di componenti)
    ugm3->setTickCount(dynamic_cast<QtCharts::QLineSeries*>(serie.first())->points().size());
    ugm3->setLabelsVisible(false);
    //GROSSI SPONI CON L'AFFERMAZIONE SOTTOSTANTE DIOM
    //addAxis(ugm3, QtCharts::QPolarChart::PolarOrientationRadial);

    // asse azimutale
    QtCharts::QCategoryAxis *componenti = new QtCharts::QCategoryAxis();
    componenti->setLabelsPosition(QtCharts::QCategoryAxis::AxisLabelsPositionOnValue);
    componenti->setRange(0, 360);
    componenti->setLabelsVisible(true);
    //GROSSI SPONI CON L'AFFERMAZIONE SOTTOSTANTE DIOM
    //addAxis(componenti, QtCharts::QPolarChart::PolarOrientationAngular);
}

void MyChart::buildBarChart(QMap<QString, QtCharts::QAbstractSeries*> serie){}

QtCharts::QLineSeries* MyChart::sommaY(QtCharts::QLineSeries *upper, QtCharts::QLineSeries *lower) {
    QVector<QPointF> puntiLower = lower->pointsVector();
    QVector<QPointF> puntiUpper = upper->pointsVector();

    for(int i=0;i<puntiLower.size();++i){
        puntiUpper[i].setY(puntiLower.at(i).y()+puntiUpper.at(i).y());
    }
    upper->replace(puntiUpper);
    return upper;
}
double MyChart::maxValueFromListSeries(QList<QtCharts::QAbstractSeries*> series) {
    double max=0;

    for(auto serie:series) {
        QtCharts::QXYSeries* seriexy = dynamic_cast<QtCharts::QXYSeries*>(serie);
        if(seriexy){
            if(maxFromSerie(seriexy)>max)
                max=maxFromSerie(seriexy);
        }
    }

    return max;
}

double MyChart::maxFromSerie(QtCharts::QXYSeries* serie) {
    double max=0;

    for(unsigned int i=0; i<serie->count(); ++i) {
        if(serie->at(i).y()>max) {
            max = serie->at(i).y();
        }
    }

    return max;
}
