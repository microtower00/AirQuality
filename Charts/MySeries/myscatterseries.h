#ifndef MYSCATTERSERIES_H
#define MYSCATTERSERIES_H

#include <QScatterSeries>

#include "Model/dati.h"

class MyScatterSerie : public QtCharts::QScatterSeries
{
public:
    MyScatterSerie(Dati*, QString comp ,QObject *parent = nullptr);
};

#endif // MYSCATTERSERIES_H
