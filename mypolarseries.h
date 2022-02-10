#ifndef MYPOLARSERIES_H
#define MYPOLARSERIES_H

#include <QLineSeries>

#include "dati.h"

class MyPolarSeries : public QtCharts::QLineSeries
{
public:
    MyPolarSeries(const QMap<QString, double>&,  const QMap<QString, double>&, const QList<QString>&, QObject *parent = nullptr);
    static QMap<QString, double>& calcolaFondoScala(const QList<QMap<QString,double>>&);

private:
    static double maxValueForComp(const QList<QMap<QString,double>>&, QString);
};

#endif // MYPOLARSERIES_H
