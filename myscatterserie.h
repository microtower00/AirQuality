#ifndef MYSCATTERSERIE_H
#define MYSCATTERSERIE_H

#include <QScatterSeries>

#include "dati.h"

class MyScatterSerie : public QtCharts::QScatterSeries
{
public:
    MyScatterSerie(const Dati&, QString comp ,QObject *parent = nullptr);
};

#endif // MYSCATTERSERIE_H
