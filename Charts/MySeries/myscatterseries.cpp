#include "myscatterseries.h"

MyScatterSerie::MyScatterSerie (Dati *dati, QString comp, QObject *)
    : QtCharts::QScatterSeries{ /*parent*/ }
{

    setMarkerSize (10);
    setName (comp);

    for (auto record : dati->getDati ())
        {
            int oraDelGiorno = Dati::getDateFromDouble (record.value ("Data"))
                                   .time ()
                                   .hour ();
            append (QPointF (
                Dati::getDateFromDouble (record.value ("Data")).time ().hour (),
                record.value (comp)));
        }
}
