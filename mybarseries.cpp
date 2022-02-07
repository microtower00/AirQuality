#include "mybarseries.h"

MybarSeries::MybarSeries(const Dati& dati, QList<QString> comp, QObject *parent)  : QtCharts::QBarSeries{parent}{
    QtCharts::QBarSet* barreComp;

    //Per ogni record, cerco se la chiave è in comp e appendo al barSet d quel comp
    for(QString chiave : dati.getChiavi()){
        for(auto record : dati.getDati()){
            barreComp = new QtCharts::QBarSet(chiave);
            for(int i = 0; i< comp.size(); i++){
                if(chiave==comp.at(i)){
                    barreComp->append(record.value(chiave));
                }
            }
        }
        append(barreComp);
    }
}
