#ifndef MYPOLARCHART_H
#define MYPOLARCHART_H

#include <QPolarChart>
#include <QValueAxis>
#include <QLineSeries>
#include <QCategoryAxis>

class MyPolarChart : public QtCharts::QPolarChart
{
public:
    MyPolarChart(QMap<QString,QtCharts::QAbstractSeries*>);
};

#endif // MYPOLARCHART_H
