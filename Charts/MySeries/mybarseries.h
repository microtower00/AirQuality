#ifndef MYBARSERIES_H
#define MYBARSERIES_H

#include <QBarSeries>
#include <QBarSet>
#include "Model/dati.h"

class MyBarSeries : public QtCharts::QBarSeries
{
public:
    MyBarSeries(Dati*, QList<QString>, QObject *parent = nullptr);
};

#endif // MYBARSERIES_H
