#ifndef MYPOLARSERIES_H
#define MYPOLARSERIES_H

#include <QLineSeries>

#include "Model/dati.h"

class MyPolarSeries : public QtCharts::QLineSeries
{
public:
    MyPolarSeries(const QList<QMap<QString, double>>&, QMap<QString, double>, QList<QString>, QObject *parent = nullptr);
    static QMap<QString, double>& calcolaFondoScala(const QList<QMap<QString,double>>&);

private:
    static double maxValueForComp(const QList<QMap<QString,double>>&, QString);
};

#endif // MYPOLARSERIES_H
