#ifndef CHARTCONTROLLER_H
#define CHARTCONTROLLER_H

#include "Model/dati.h"
#include "mychart.h"
#include "mybarseries.h"
#include "myscatterserie.h"
#include "mypolarseries.h"
#include "mypolarchart.h"

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
    Q_OBJECT
private:
    QMap<QString,double> MASSIMICONSENTITI;
    QtCharts::QValueAxis *asseY;
    QtCharts::QDateTimeAxis *asseX;
    const Dati& data;
    QStringList comp;
public:
    MyChartView(const Dati&);

    void setCompScelti(const QStringList&);

    QMap<QString, QtCharts::QLineSeries*> genericLAchart();

    void lineChart();
    void areaChart();
    void barChart();
    void radarChart();
    void scatterChart();

    void resetView();

    QtCharts::QLineSeries* sommaY (QtCharts::QLineSeries*, QtCharts::QLineSeries*) const;
    static double maxValueFromListSeries(QList<QtCharts::QAbstractSeries*>);
    static double maxFromSerie(QtCharts::QXYSeries*);
    static double maxFromBarSets(QtCharts::QBarSeries*);

signals:
    void chartPronto();
    void tipoChartPronto(const MyChart::GraphType&);
};

#endif // CHARTCONTROLLER_H
