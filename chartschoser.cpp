#include "chartschoser.h"
#include "chartsviewer.h"
#include <QVBoxLayout>

ChartsChoser::ChartsChoser(QWidget* parent) : QMainWindow(parent)
{
    testLab = new QLabel("test");
    QLabel* testLab2 = new QLabel("test2");
    QLabel* testLab3 = new QLabel("test3");
    QLabel* testLab4 = new QLabel("test4");
    QLabel* testLab5 = new QLabel("test5");
    QLabel* testLab6 = new QLabel("test6");
    QGridLayout* gridCharts = new QGridLayout;

    resize(250,150);

    testFin = new QWidget();
    testFin->setLayout(gridCharts);

    gridCharts->addWidget(testLab);
    gridCharts->addWidget(testLab2);
    gridCharts->addWidget(testLab3);
    gridCharts->addWidget(testLab4);
    gridCharts->addWidget(testLab5);
    gridCharts->addWidget(testLab6);

    setCentralWidget(testFin);
}

ChartsChoser::~ChartsChoser(){}
