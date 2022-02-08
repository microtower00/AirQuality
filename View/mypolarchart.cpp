#include "mypolarchart.h"

MyPolarChart::MyPolarChart(QMap<QString,QtCharts::QAbstractSeries*> serie){

    QtCharts::QValueAxis *ugm3 = new QtCharts::QValueAxis;
    ugm3->setRange(0, 100);
    //Setto il numero di ticks uguale al numero di punti in una serie (Cioè il numero di componenti)
    ugm3->setTickCount(dynamic_cast<QtCharts::QLineSeries*>(serie.first())->points().size());
    ugm3->setLabelsVisible(false);
    addAxis(ugm3, QtCharts::QPolarChart::PolarOrientationRadial);

    // asse azimutale
    QtCharts::QCategoryAxis *componenti = new QtCharts::QCategoryAxis();
    componenti->setLabelsPosition(QtCharts::QCategoryAxis::AxisLabelsPositionOnValue);
    componenti->setRange(0, 360);
    componenti->setLabelsVisible(true);
    addAxis(componenti, QtCharts::QPolarChart::PolarOrientationAngular);

    //Per ogni serie setto il nome, e aggiungo al grafico
    for(auto chiave : serie.keys()){
        addSeries(serie.value(chiave));
        serie.value(chiave)->setName(chiave);
        serie.value(chiave)->attachAxis(ugm3);
        serie.value(chiave)->attachAxis(componenti);

    }
}
