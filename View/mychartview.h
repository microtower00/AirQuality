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
    const Dati& data;
    QStringList& comp;
public:
    MyChartView(const Dati&);

    void setCompScelti(const QStringList&);

    QMap<QString, QtCharts::QLineSeries*> genericLAchart(const QStringList&);

    void lineChart();
    void areaChart();
    void barChart();
    void radarChart();
    void scatterChart();

    void resetView();

    void sommaY(QtCharts::QLineSeries&, QtCharts::QLineSeries*);
    double maxValueFromListSeries(QList<QtCharts::QLineSeries*>);
    double maxFromSerie(QtCharts::QXYSeries*);

};

#endif // CHARTCONTROLLER_H
