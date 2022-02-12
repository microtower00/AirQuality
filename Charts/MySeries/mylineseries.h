#ifndef MYLINESERIES_H
#define MYLINESERIES_H

#include <QLineSeries>
#include "Model/dati.h"

class MyLineSeries : public QtCharts::QLineSeries
{
public:
    MyLineSeries(Dati*, QString, QObject *parent = nullptr);
};

#endif // MYLINESERIES_H
