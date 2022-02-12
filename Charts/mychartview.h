#ifndef CHARTCONTROLLER_H
#define CHARTCONTROLLER_H

#include "Charts/MyCharts/mychart.h"
#include "Charts/MyCharts/mypolarchart.h"
#include "Charts/MySeries/mybarseries.h"
#include "Charts/MySeries/mypolarseries.h"
#include "Charts/MySeries/myscatterseries.h"
#include "Model/dati.h"

#include <QAreaSeries>
#include <QBarCategoryAxis>
#include <QBarSeries>
#include <QBarSet>
#include <QCategoryAxis>
#include <QChartView>
#include <QDateTimeAxis>
#include <QLineSeries>
#include <QMainWindow>
#include <QPolarChart>
#include <QScatterSeries>
#include <QValueAxis>
#include <typeinfo>

class MyChartView : public QtCharts::QChartView
{
    Q_OBJECT
  private:
    QMap<QString, double> MASSIMICONSENTITI;
    QtCharts::QValueAxis *asseY;
    QtCharts::QDateTimeAxis *asseX;
    Dati *data;
    QStringList comp;

  public:
    MyChartView (Dati *);

    void setCompScelti (const QStringList &);

    QMap<QString, QtCharts::QLineSeries *> genericLAchart ();

    void lineChart ();
    void areaChart ();
    void barChart ();
    void radarChart ();
    void scatterChart ();

    void resetView ();

    QtCharts::QLineSeries *sommaY (QtCharts::QLineSeries *,
                                   QtCharts::QLineSeries *) const;
    static double maxValueFromListSeries (QList<QtCharts::QAbstractSeries *>);
    static double maxFromSerie (QtCharts::QXYSeries *);
    static double maxFromBarSets (QtCharts::QBarSeries *);

  signals:
    void chartPronto ();
    void tipoChartPronto (const MyChart::GraphType &);
};

#endif // CHARTCONTROLLER_H
