#include "mypolarseries.h"

MyPolarSeries::MyPolarSeries(const QList<QMap<QString, double>>& giorno,  QMap<QString, double> fondoScala, QList<QString> componenti, QObject *parent) : QtCharts::QLineSeries{parent}{
    QMap<QString,double> media;

    //Per ogni ora del giorno, ciclo su ogni componente e aggiungo facendo la media
    for(auto record : giorno){
        for(QString comp : componenti){
            media.insert(comp, media.value(comp)+record.value(comp)/2);
        }
    }

    for(QString comp:componenti){
        //Segno ai gradi giusti per ogni componente
        append(QPointF(360/componenti.size()*componenti.indexOf(comp), media.value(comp)*100/fondoScala.value(comp)));
    }

    //Chiudo il cerchio
    append(QPointF(360, media.value(componenti.first())*100/fondoScala.values().at(0)));
}


//fornisce metodo di utility per calcolare quali saranno i valori di fondoScala a partire da una lista di mappe
QMap<QString,double>& MyPolarSeries::calcolaFondoScala(const QList<QMap<QString,double>>& mappe){
    QMap<QString,double>* massimi = new QMap<QString,double>();
    for(QString comp: mappe.at(0).keys())
        massimi->insert(comp,MyPolarSeries::maxValueForComp(mappe,comp));
    return *massimi;
}

//usato in calcolaFondoScala
double MyPolarSeries::maxValueForComp(const QList<QMap<QString, double>>& mappe, QString comp){
    double max = 0;
    for(auto record: mappe)
        max = record.value(comp) > max ? record.value(comp): max;
    return max;
}
