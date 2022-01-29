#ifndef CHARTCONTROLLER_H
#define CHARTCONTROLLER_H

#include "Model/dati.h"

#include <QMainWindow>
#include <QChartView>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QDebug>
#include <QValueAxis>
#include <QPolarChart>
#include <QAreaSeries>
#include <QColor>
#include <QScatterSeries>
#include <QCategoryAxis>
#include <typeinfo>

class MyChartView : public QtCharts::QChartView {
public:
    MyChartView();

    void lineChart(const Dati&, QStringList);
    void barChart(const Dati&, QStringList);
    void radarChart(const Dati&, QStringList);
    void areaChart(const Dati&, QStringList);

    void resetView();
};

#endif // CHARTCONTROLLER_H
