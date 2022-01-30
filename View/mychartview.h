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
private:
    QtCharts::QValueAxis *asseY;
    QtCharts::QDateTimeAxis *asseX;
public:
    MyChartView();

    QMap<QString, QtCharts::QLineSeries*> genericLAchart(const Dati&, QStringList);

    void lineChart(const Dati&, QStringList);
    void barChart(const Dati&, QStringList);
    void radarChart(const Dati&, QStringList);
    void areaChart(const Dati&, QStringList);

    void resetView();

    void sommaY(QtCharts::QLineSeries&, QtCharts::QLineSeries*);
    double maxValueFromListSeries(QList<QtCharts::QLineSeries*>);
};

#endif // CHARTCONTROLLER_H
