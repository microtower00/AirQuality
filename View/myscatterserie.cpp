#include "myscatterserie.h"

MyScatterSerie::MyScatterSerie(const Dati& dati, QString comp,QObject *) : QtCharts::QScatterSeries{/*parent*/}{

    setMarkerSize(10);
    setName(comp);

    for (auto record : dati.getDati()){
        append(QPointF((Dati::getDateFromDouble(record.value("Data")).time().msecsSinceStartOfDay())/3600000, record.value(comp)));
    }
}
