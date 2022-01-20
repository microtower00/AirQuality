#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H

#include "Model/dati.h"

#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QDebug>
#include <QValueAxis>
#include <QPolarChart>
#include <QValueAxis>

class MyChartView : public QtCharts::QChartView
{
public:
    MyChartView();

    void lineChart(const Dati&, QString);
    void barChart(const Dati&);
    void radarChart(const Dati&);
    void areaChart(const Dati&);

    void resetView();
};

#endif // MYCHARTVIEW_H