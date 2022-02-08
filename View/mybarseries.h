#ifndef MYBARSERIES_H
#define MYBARSERIES_H

#include <QBarSeries>
#include <QBarSet>
#include <QDebug>
#include "Model/dati.h"

class MyBarSeries : public QtCharts::QBarSeries
{
public:
    MyBarSeries(const Dati&, QList<QString>, QObject *parent = nullptr);
};//Commit di prova prima di fottere tutto

#endif // MYBARSERIES_H
