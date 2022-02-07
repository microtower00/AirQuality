#include "mybarseries.h"

MyBarSeries::MyBarSeries(const Dati& dati, QList<QString> comp, QObject *parent)  : QtCharts::QBarSeries{parent}{
    QList<QtCharts::QBarSet*> barreComp;
    QtCharts::QBarSet* temp;

    //Per ogni record, cerco se la chiave è in comp e appendo al barSet d quel comp

    for(int i = 0; i< comp.size(); i++){
        temp = new QtCharts::QBarSet(comp.at(i));
        for(auto record : dati.getDati()){
            temp->append(record.value(comp.at(i)));
            qDebug()<<"Inserisco barra su componente "+ comp.at(i);
        }
        barreComp.push_back(temp);
    }
    append(barreComp);
}
