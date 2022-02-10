#ifndef MYLINESERIES_H
#define MYLINESERIES_H

#include <QLineSeries>
#include <QDebug>
#include "dati.h"

class MyLineSeries : public QtCharts::QLineSeries
{
public:
    MyLineSeries(const Dati&, QString, QObject *parent = nullptr);
};

#endif // MYLINESERIES_H
