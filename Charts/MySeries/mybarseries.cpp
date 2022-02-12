#include "mybarseries.h"

MyBarSeries::MyBarSeries(Dati* data, QList<QString> comp, QObject *parent)  : QtCharts::QBarSeries{parent}{
    QList<QtCharts::QBarSet*> barreComp;
    QtCharts::QBarSet* temp;

    QList<QMap<QString, double>> dati = data->getDati();

    QVector<QMap<QString,double>> medieIntervallo = QVector<QMap<QString,double>>(10);
    double secondiInizio = dati.first().value("Data");
    double decimoIntervallo = (dati.last().value("Data")-secondiInizio)/10;

    for(int i = 0; i<10; ++i){
        for(auto record:data->getDati()){
            if(record.value("Data")<secondiInizio+decimoIntervallo*(i+1) && record.value("Data")>=secondiInizio+decimoIntervallo*i){
                for(QString c : comp){
                    medieIntervallo[i].insert(c,(medieIntervallo[i].value(c)+record.value(c))/2);
                }
            }
        }
    }

    for(QString c : comp){
        temp = new QtCharts::QBarSet(c);
        //Ad ogni intervallo la sua media
        for(int i = 0; i<10; ++i){
            temp->append(medieIntervallo[i].value(c));
        }
        barreComp.push_back(temp);
    }
    append(barreComp);
}
