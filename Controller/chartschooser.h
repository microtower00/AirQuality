#ifndef CHARTSCHOOSER_H
#define CHARTSCHOOSER_H

#include "Model/dati.h"
#include "View/mychartview.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QDebug>
#include <QDateTimeAxis>
#include <QSizePolicy>
#include <QGroupBox>
#include <QCheckBox>

class ChartsChooser : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChartsChooser(const Dati&, QWidget *parent = nullptr);
public slots:
    void displayChart();
signals:
private:
    Dati data;

    QWidget* finestra;

    QVBoxLayout* mainLayout;
    QGroupBox* sceltaGraf;
    QHBoxLayout* sceltaGrafLayout;
    QGroupBox *sceltaComp;

    QComboBox* grafici;
    QCheckBox* area;

    QGridLayout* grigliaComp;

    QList<QCheckBox*> cbComponenti;

    QPushButton* conferma;

    MyChartView* grafico;

    /*QLabel* testLab;
    QPushButton* bottLinee;
    QPushButton* bottArea;
    QPushButton* bottIsto;
    QPushButton* bottPlot;
    QPushButton* bottRadar;

    QWidget* testFin;

    QGridLayout* gridCharts;

    QHBoxLayout *hLayout;

    QPushButton *sceltaArea;

    //QScrollArea* scrollA;*/
};

#endif // CHARTSCHOOSER_H
