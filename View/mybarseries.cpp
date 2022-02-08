#include "mybarseries.h"

MyBarSeries::MyBarSeries(const Dati& dati, QList<QString> comp, QObject *parent)  : QtCharts::QBarSeries{parent}{
    QList<QtCharts::QBarSet*> barreComp;
    QtCharts::QBarSet* temp;

    QVector<QMap<QString,double>> medieIntervallo = QVector<QMap<QString,double>>(10);
    double secondiInizio = dati.getDati().first().value("Data");
    double decimoIntervallo = (dati.getDati().last().value("Data")-secondiInizio)/10;

    for(int i = 0; i<10; ++i){
        for(auto record:dati.getDati()){
            if(record.value("Data")<secondiInizio+decimoIntervallo*(i+1) && record.value("Data")>=secondiInizio+decimoIntervallo*i){
                for(QString c : comp){
                    medieIntervallo[i].insert(c,(medieIntervallo[i].value(c)+record.value(c))/2);
                }
            }
        }
    }

    //Inserisco le barre
    for(QString c : comp){
        //Un barset per ogni componente
        temp = new QtCharts::QBarSet(c);
        //Ad ogni intervallo la sua media
        for(int i = 0; i<10; ++i){
            temp->append(medieIntervallo[i].value(c));
        }
        barreComp.push_back(temp);
    }
    append(barreComp);
}
