#ifndef MYBARSERIES_H
#define MYBARSERIES_H

#include <QBarSeries>
#include <QBarSet>
#include <QDebug>
#include "dati.h"

class MyBarSeries : public QtCharts::QBarSeries
{
public:
    MyBarSeries(const Dati&, QList<QString>, QObject *parent = nullptr);
};

#endif // MYBARSERIES_H
