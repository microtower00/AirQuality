#include "myscatterserie.h"

MyScatterSerie::MyScatterSerie(const Dati& dati, QString comp, QObject *) : QtCharts::QScatterSeries{/*parent*/}{

    setMarkerSize(10);
    setName(comp);

    for (auto record : dati.getDati()){
        int oraDelGiorno = Dati::getDateFromDouble(record.value("Data")).time().hour();
        qDebug()<<oraDelGiorno;
        append(QPointF(Dati::getDateFromDouble(record.value("Data")).time().hour(), record.value(comp)));
    }
}
