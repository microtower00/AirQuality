#ifndef MYCHART_H
#define MYCHART_H

#include <QChart>
#include <QAbstractSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QAreaSeries>
#include <QLineSeries>
#include <QPolarChart>
#include <QCategoryAxis>
#include <QValueAxis>
#include <QScatterSeries>
#include <QBarCategoryAxis>
#include <QDebug>


#include "mylineseries.h"



class MyChart : public QtCharts::QChart
{
    Q_ENUMS(GraphType);
public:
    enum class GraphType{
        LineG,
        AreaG,
        BarG,
        ScatterG,
        PolarG
    };

    MyChart(QMap<QString,QtCharts::QAbstractSeries*>, MyChart::GraphType);

    void buildLineChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildScatterChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildPolarChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildBarChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildAreaChart(QMap<QString,QtCharts::QAbstractSeries*>);

    static double maxValueFromListSeries(QList<QtCharts::QAbstractSeries*>);
    static double maxFromSerie(QtCharts::QXYSeries*);
    static QtCharts::QLineSeries* sommaY(QtCharts::QLineSeries *, QtCharts::QLineSeries *);



};


#endif // MYCHART_H
