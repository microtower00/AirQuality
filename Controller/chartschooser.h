#ifndef CHARTSCHOOSER_H
#define CHARTSCHOOSER_H

#include "Model/dati.h"
#include "View/mychartview.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>

class ChartsChooser : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChartsChooser(const Dati&, QWidget *parent = nullptr);
public slots:
    //void createLineChart();
    //void createBarChart();

    void displayLineChart();
    void displayBarChart();
signals:
private:
    Dati data;

    QLabel* testLab;
    QPushButton* bottLinee;
    QPushButton* bottArea;
    QPushButton* bottIsto;
    QPushButton* bottPlot;
    QPushButton* bottRadar;

    QComboBox* componenti;

    QWidget* testFin;

    QGridLayout* gridCharts;

    MyChartView* grafico;

};

#endif // CHARTSCHOOSER_H
