#include "mylineseries.h"

MyLineSeries::MyLineSeries(const Dati& dati, QString componente, QObject *parent) : QtCharts::QLineSeries{parent}{
    QList<QMap<QString,double>>listaDati = dati.getDati();
    for(QMap<QString,double> entry:listaDati){

        qDebug()<<"QPointF(X,Y): ("+QString::number(Dati::getDateFromDouble(entry.value("Data")).toMSecsSinceEpoch())+", "+QString::number(entry.value(componente))+")";
        qDebug()<<"Punto del componente " + componente;
        append(QPointF(Dati::getDateFromDouble(entry.value("Data")).toMSecsSinceEpoch(),entry.value(componente)));
    }

}
