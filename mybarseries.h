#ifndef MYBARSERIES_H
#define MYBARSERIES_H

#include <QBarSeries>
#include <QBarSet>

#include "Model/dati.h"

class MybarSeries : public QtCharts::QBarSeries
{
public:
    MybarSeries(const Dati&, QList<QString>, QObject *parent = nullptr);
};//Commit di prova prima di fottere tutto

#endif // MYBARSERIES_H
