#include "mylineseries.h"

MyLineSeries::MyLineSeries (Dati *dati, QString componente, QObject *parent)
    : QtCharts::QLineSeries{ parent }
{
    QList<QMap<QString, double> > listaDati = dati->getDati ();
    for (QMap<QString, double> entry : listaDati)
        {
            append (QPointF (entry.value ("Data") * 1000,
                             entry.value (componente)));
        }
}
