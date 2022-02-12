#ifndef MYCHART_H
#define MYCHART_H

#include <QAbstractSeries>
#include <QAreaSeries>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QCategoryAxis>
#include <QChart>
#include <QDateTimeAxis>
#include <QLineSeries>
#include <QPolarChart>
#include <QScatterSeries>
#include <QValueAxis>

#include "Charts/MySeries/mylineseries.h"

class MyChart : public QtCharts::QChart
{
    Q_ENUMS (GraphType);

  public:
    enum class GraphType
    {
        LineG,
        AreaG,
        BarG,
        ScatterG,
        RadarG
    };

    static GraphType stringToEnum (const QString &);

    MyChart (QMap<QString, QtCharts::QAbstractSeries *>, MyChart::GraphType);

    static double maxValueFromListSeries (QList<QtCharts::QAbstractSeries *>);
    static double maxFromSerie (QtCharts::QXYSeries *);
    static double maxFromBarSets (QtCharts::QBarSeries *);
    static QtCharts::QLineSeries *sommaY (QtCharts::QLineSeries *,
                                          QtCharts::QLineSeries *);

  private:
    void buildLineChart (QMap<QString, QtCharts::QAbstractSeries *>);
    void buildScatterChart (QMap<QString, QtCharts::QAbstractSeries *>);
    void buildPolarChart (QMap<QString, QtCharts::QAbstractSeries *>);
    void buildBarChart (QMap<QString, QtCharts::QAbstractSeries *>);
    void buildAreaChart (QMap<QString, QtCharts::QAbstractSeries *>);
    QPair<QtCharts::QDateTimeAxis *, QtCharts::QValueAxis *>
        setLineAxis (QMap<QString, QtCharts::QAbstractSeries *>);
};

#endif // MYCHART_H
