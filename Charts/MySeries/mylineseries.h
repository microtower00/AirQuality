#ifndef MYLINESERIES_H
#define MYLINESERIES_H

#include "Model/dati.h"
#include <QLineSeries>

class MyLineSeries : public QtCharts::QLineSeries
{
  public:
    MyLineSeries (Dati *, QString, QObject *parent = nullptr);
};

#endif // MYLINESERIES_H
