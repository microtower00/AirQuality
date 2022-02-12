#ifndef MYPOLARCHART_H
#define MYPOLARCHART_H

#include <QCategoryAxis>
#include <QLineSeries>
#include <QPolarChart>
#include <QValueAxis>

class MyPolarChart : public QtCharts::QPolarChart
{
  public:
    MyPolarChart (QMap<QString, QtCharts::QAbstractSeries *>);
};

#endif // MYPOLARCHART_H
