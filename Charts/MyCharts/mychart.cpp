#include "mychart.h"

MyChart::MyChart(QMap<QString,QtCharts::QAbstractSeries*> serie, MyChart::GraphType gt)
{
    setAnimationOptions(MyChart::SeriesAnimations);
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignBottom);

    switch(gt){
    case MyChart::GraphType::LineG :
        buildLineChart(serie);break;
    case MyChart::GraphType::AreaG :
        buildAreaChart(serie);break;
    case MyChart::GraphType::ScatterG :
        buildScatterChart(serie);break;
    case MyChart::GraphType::BarG :
        buildBarChart(serie);break;
    }

}

QPair<QtCharts::QDateTimeAxis*,QtCharts::QValueAxis*> MyChart::setLineAxis(QMap<QString, QtCharts::QAbstractSeries*> serie){
    QtCharts::QDateTimeAxis* asseX = new QtCharts::QDateTimeAxis;
    asseX->setTickCount(12);
    addAxis(asseX, Qt::AlignBottom);

    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    addAxis(asseY, Qt::AlignLeft);

    if(serie.value("aqi")){
        asseY->setMax(6);
        asseY->setMin(1);
        asseY->setTickCount(6);
    }else{
        //setto il massimo di Y al massimo valore tra tutte le serie
        asseY->setMin(0);
        asseY->setMax(maxValueFromListSeries(serie.values())+.03*maxValueFromListSeries(serie.values()));
        asseY->setTickCount(10);
    }

    QtCharts::QLineSeries* serieLine = dynamic_cast<QtCharts::QLineSeries*>(serie.first());
    int secondiIntervallo = (serieLine->points().at(serieLine->points().size()-1).x()-serieLine->points().at(0).x())/1000;

    if(secondiIntervallo<7*86400)//meno di 3 giorni
        asseX->setFormat("dd/MM hh:mm");
    else if(secondiIntervallo<365*86400)
        asseX->setFormat("dd/MM");
    else
        asseX->setFormat("dd/MM/yy");

    asseY->setMinorTickCount(asseY->tickCount()/4);
    return QPair<QtCharts::QDateTimeAxis*,QtCharts::QValueAxis*>(asseX,asseY);
}

void MyChart::buildLineChart(QMap<QString, QtCharts::QAbstractSeries*> serie){
    QPair<QtCharts::QDateTimeAxis*,QtCharts::QValueAxis*> assi = setLineAxis(serie);

    //Per ogni serie nella mapps setto nome e collego gli assi
    for(auto it=serie.begin(); it!=serie.end(); ++it){
        addSeries(*it);
        it.value()->setName(it.key());
        it.value()->attachAxis(assi.first);
        it.value()->attachAxis(assi.second);
    }
    setTitle("Andamento della densità dei componenti nel tempo (µg/m³ nel tempo)");
}

void MyChart::buildAreaChart(QMap<QString, QtCharts::QAbstractSeries *> series){
    QPair<QtCharts::QDateTimeAxis*,QtCharts::QValueAxis*> assi = setLineAxis(series);
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
        aSeries->attachAxis(assi.first);
        aSeries->attachAxis(assi.second);
    }

    assi.second->setMax(maxValueFromListSeries(series.values())+.03*maxValueFromListSeries(series.values()));

    setTitle("Andamento della densità dei componenti nel tempo (µg/m³ nel tempo)");
}

void MyChart::buildScatterChart(QMap<QString, QtCharts::QAbstractSeries*> serie){

    QtCharts::QScatterSeries* sSerie = static_cast<QtCharts::QScatterSeries*>(serie.first());
    // asse X
    QtCharts::QValueAxis* asseX = new QtCharts::QValueAxis;
    asseX->setTickCount(24);
    addAxis(asseX, Qt::AlignBottom);

    // asse Y
    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    // lascio spazio sopra l'ultimo pallino
    asseY->setRange(0, maxFromSerie(sSerie)+(maxFromSerie(sSerie)/sSerie->markerSize()));
    addAxis(asseY, Qt::AlignLeft);

    addSeries(sSerie);
    sSerie->attachAxis(asseX);
    sSerie->attachAxis(asseY);

    setTitle("Densità nell'aria dei componenti nelle ore della giornata (µg/m³ nel tempo)");
}

void MyChart::buildBarChart(QMap<QString, QtCharts::QAbstractSeries*> serie){
    //Posso perch`prevedo di passargli una sola serie, con tutti i barset
    addSeries(serie.first());

    QtCharts::QValueAxis* asseY = new QtCharts::QValueAxis();
    QList<QtCharts::QAbstractSeries*> param;
    param.push_back(serie.first());
    asseY->setMax(MyChart::maxValueFromListSeries(param)+MyChart::maxValueFromListSeries(param)*.03);
    addAxis(asseY,Qt::AlignLeft);
    serie.first()->attachAxis(asseY);


    QtCharts::QBarCategoryAxis* asse = new QtCharts::QBarCategoryAxis();
    //asse->setRange(QDateTime::currentDateTime().addMonths(-1).toString(),QDateTime::currentDateTime().toString());
    addAxis(asse,Qt::AlignBottom);
    serie.first()->attachAxis(asse);

    setTitle("Media della densità dei componenti nel tempo (µg/m³ nel tempo)");
}

QtCharts::QLineSeries* MyChart::sommaY(QtCharts::QLineSeries *upper, QtCharts::QLineSeries *lower) {

    QVector<QPointF> puntiLower = lower->pointsVector();
    QVector<QPointF> puntiUpper = upper->pointsVector();
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

    for(int i=0; i<serie->count(); ++i) {
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

MyChart::GraphType MyChart::stringToEnum(const QString& stringGraf) {
    if(stringGraf=="A linee")
        return GraphType::LineG;
    else if (stringGraf=="Ad aree")
        return GraphType::AreaG;
    else if (stringGraf=="Istogramma")
        return GraphType::BarG;
    else if (stringGraf=="Plot")
        return GraphType::ScatterG;
    else if (stringGraf=="Radar")
        return GraphType::RadarG;
}

