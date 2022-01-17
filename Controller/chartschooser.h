#ifndef CHARTSCHOOSER_H
#define CHARTSCHOOSER_H

#include "Model/dati.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QDateTimeAxis>
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>

class ChartsChooser : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChartsChooser(const Dati&, QWidget *parent = nullptr);
public slots:
    void createLineChart();
    void createBarChart();
signals:
private:
    Dati data;

    QLabel* testLab;
    QPushButton* bottLinee;
    QPushButton* bottArea;
    QPushButton* bottIsto;
    QPushButton* bottPlot;
    QPushButton* bottRadar;

    QWidget* testFin;

    QGridLayout* gridCharts;

    QtCharts::QChartView* grafico;

};

#endif // CHARTSCHOOSER_H
