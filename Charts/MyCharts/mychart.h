#ifndef MYCHART_H
#define MYCHART_H

#include <QChart>
#include <QAbstractSeries>
#include <QDateTimeAxis>
#include <QValueAxis>
#include <QAreaSeries>
#include <QLineSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QPolarChart>
#include <QCategoryAxis>
#include <QScatterSeries>
#include <QBarCategoryAxis>
#include <QDebug>


#include "Charts/MySeries/mylineseries.h"



class MyChart : public QtCharts::QChart
{
    Q_ENUMS(GraphType);
public:
    enum class GraphType{
        LineG,
        AreaG,
        BarG,
        ScatterG,
        RadarG //anche se non è il posto perfetto
    };

    static GraphType stringToEnum(const QString&);

    MyChart(QMap<QString,QtCharts::QAbstractSeries*>, MyChart::GraphType);

    static double maxValueFromListSeries(QList<QtCharts::QAbstractSeries*>);
    static double maxFromSerie(QtCharts::QXYSeries*);
    static double maxFromBarSets(QtCharts::QBarSeries*);
    static QtCharts::QLineSeries* sommaY(QtCharts::QLineSeries *, QtCharts::QLineSeries *);

private:
    void buildLineChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildScatterChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildPolarChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildBarChart(QMap<QString,QtCharts::QAbstractSeries*>);
    void buildAreaChart(QMap<QString,QtCharts::QAbstractSeries*>);



};


#endif // MYCHART_H