#ifndef MYBARSERIES_H
#define MYBARSERIES_H

#include <QBarSeries>
#include <QBarSet>

#include "Model/dati.h"

class MybarSeries : public QtCharts::QBarSeries
{
public:
    MybarSeries(const Dati&, QList<QString>, QObject *parent = nullptr);
};

#endif // MYBARSERIES_H
