#ifndef MYBARSERIES_H
#define MYBARSERIES_H

#include "Model/dati.h"
#include <QBarSeries>
#include <QBarSet>

class MyBarSeries : public QtCharts::QBarSeries
{
  public:
    MyBarSeries (Dati *, QList<QString>, QObject *parent = nullptr);
};

#endif // MYBARSERIES_H
