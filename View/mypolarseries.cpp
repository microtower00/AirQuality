#include "mypolarseries.h"

MyPolarSeries::MyPolarSeries(const QMap<QString, double>& mediaPrimoGiorno,  const QMap<QString, double>& fondoScala, const QList<QString>& componenti, QObject *parent) : QtCharts::QLineSeries{parent}{

    for(QString comp:componenti){
        //Segno ai gradi giusti per ogni componente
        append(QPointF(360/componenti.size()*componenti.indexOf(comp), mediaPrimoGiorno.value(comp)*100/fondoScala.value(comp)));
        qDebug()<<"Inserisco punto a "+QString::number(360/componenti.size()*componenti.indexOf(comp))+" e al "+QString::number(mediaPrimoGiorno.value(comp)*100/fondoScala.value(comp));
    }

    //Chiudo il cerchio
    append(QPointF(360, mediaPrimoGiorno.value(componenti.first())*100/fondoScala.value(componenti.first())));
    qDebug()<<"Inserisco punto a "+QString::number(360)+" gradi e al "+QString::number(mediaPrimoGiorno.value(componenti.first())*100/fondoScala.values().at(0))+"%, comp: "+ componenti.first();
}


//fornisce metodo di utility per calcolare quali saranno i valori di fondoScala a partire da una lista di mappe
QMap<QString,double>& MyPolarSeries::calcolaFondoScala(const QList<QMap<QString,double>>& mappe){
    QMap<QString,double>* massimi = new QMap<QString,double>();
    for(auto comp: mappe.at(0).keys())
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
