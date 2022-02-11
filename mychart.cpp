#include "mychart.h"

MyChart::MyChart(QMap<QString,QtCharts::QAbstractSeries*> serie, MyChart::GraphType gt)
{

    switch(gt){
    case MyChart::GraphType::LineG :
        buildLineChart(serie);
        qDebug()<<"Costruisco un LineG";break;
    case MyChart::GraphType::AreaG :
        buildAreaChart(serie);
        qDebug()<<"Costruisco un AreaG";break;
    case MyChart::GraphType::ScatterG :
        buildScatterChart(serie);
        qDebug()<<"Costruisco un ScatterG";break;
    case MyChart::GraphType::BarG :
        buildBarChart(serie);
        qDebug()<<"Costruisco un BarG";break;
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
    asseY->setMax(serie.firstKey()!="aqi" ? maxValueFromListSeries(serie.values()) : maxValueFromListSeries(serie.values())+1);
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
    //Sistemo le Y per stacked area chart
    for(auto it=series.begin()+1; it!=series.end(); ++it)
            *it=sommaY(dynamic_cast<QtCharts::QLineSeries*>(*it), dynamic_cast<QtCharts::QLineSeries*>(*(it-1)));

    //per ogni serie nella mappa assegno il nome del componente e i relativi assi
    QtCharts::QAreaSeries *aSeries;
    QtCharts::QLineSeries* lowerSerie;
    for(auto it=series.begin(); it!=series.end(); ++it){
        lowerSerie = it!=series.begin() ? dynamic_cast<QtCharts::QLineSeries*>(*(it-1)) : Q_NULLPTR;
        aSeries = new QtCharts::QAreaSeries(dynamic_cast<QtCharts::QLineSeries*>(*it),lowerSerie);
        aSeries->setBorderColor(QColor::fromRgba64(0,0,0,0));
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
void MyChart::buildScatterChart(QMap<QString, QtCharts::QAbstractSeries*> serie){

    QtCharts::QScatterSeries* sSerie = static_cast<QtCharts::QScatterSeries*>(serie.first());
    // asse X
    //asseX = new QtCharts::QDateTimeAxis;
    //asseX->setFormat("h:mm");
    QtCharts::QValueAxis* asseX2 = new QtCharts::QValueAxis();
    asseX2->setTickCount(24);
    addAxis(asseX2, Qt::AlignBottom);

    // asse Y
    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    // lascio spazio sopra l'ultimo pallino
    asseY->setRange(0, maxFromSerie(sSerie)+(maxFromSerie(sSerie)/sSerie->markerSize()));
    addAxis(asseY, Qt::AlignLeft);

    addSeries(sSerie);
    sSerie->attachAxis(asseX2);
    sSerie->attachAxis(asseY);
}

void MyChart::buildBarChart(QMap<QString, QtCharts::QAbstractSeries*> serie){
    //Posso perch`prevedo di passargli una sola serie, con tutti i barset
    addSeries(serie.first());

    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    QList<QtCharts::QAbstractSeries*> param;
    param.push_back(serie.first());
    asseY->setMax(MyChart::maxValueFromListSeries(param));
    addAxis(asseY,Qt::AlignLeft);
    serie.first()->attachAxis(asseY);


    QtCharts::QBarCategoryAxis* asse = new QtCharts::QBarCategoryAxis();
    asse->setRange(QDateTime::currentDateTime().addMonths(-1).toString(),QDateTime::currentDateTime().toString());
    addAxis(asse,Qt::AlignBottom);
    serie.first()->attachAxis(asse);

    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignBottom);
}

QtCharts::QLineSeries* MyChart::sommaY(QtCharts::QLineSeries *upper, QtCharts::QLineSeries *lower) {

    QVector<QPointF> puntiLower = lower->pointsVector();
    QVector<QPointF> puntiUpper = upper->pointsVector();

    qDebug()<<"Si può morire per aver trattenuto un crash per così tanto tempo";
    for(auto puntoL:puntiLower){
        puntiUpper[puntiLower.indexOf(puntoL)].setY(puntiLower.at(puntiLower.indexOf(puntoL)).y()+puntiUpper.at(puntiLower.indexOf(puntoL)).y());
    }
    upper->replace(puntiUpper);
    return upper;
}

double MyChart::maxValueFromListSeries(QList<QtCharts::QAbstractSeries*> series) {
    double max=0;

    if(dynamic_cast<QtCharts::QLineSeries*>(series.first())){
        for(auto serie:series) {
            QtCharts::QLineSeries* lSerie = dynamic_cast<QtCharts::QLineSeries*>(serie);
            if(MyChart::maxFromSerie(lSerie)>max)
                max=MyChart::maxFromSerie(lSerie);
        }
    }else if(dynamic_cast<QtCharts::QBarSeries*>(series.first())){
        for(auto serie:series) {
            QtCharts::QBarSeries* barSerie = dynamic_cast<QtCharts::QBarSeries*>(serie);
            if(MyChart::maxFromBarSets(barSerie)>max)
                max=MyChart::maxFromBarSets(barSerie);
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

double MyChart::maxFromBarSets(QtCharts::QBarSeries* barre){
    double max=0;
    for(auto barSet:barre->barSets()){
        for(int i=0;i<barSet->count();++i){
            if(barSet->at(i)>max)
                max = barSet->at(i);
        }
    }
    return max;
}