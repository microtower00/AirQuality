#ifndef CHARTSVIEWER_H
#define CHARTSVIEWER_H

#include "chartschooser.h"

#include <QMainWindow>
#include <QGroupBox>
#include <QTextEdit>

class ChartsViewer : public QMainWindow
{
    Q_OBJECT

public:
    ChartsViewer(const Dati&, QWidget *parent = nullptr);

public slots:
   void mostraChart();
   void mostraTable();

signals:

private:
    QHBoxLayout* layoutGraf;
    QHBoxLayout* layoutDescr;

    ChartsChooser* GBcontrolli;
    QGroupBox* GBdescrizione;
    QGroupBox* GBgrafico;

    DataViewer* tabella;
    MyChartView* grafico;

    QGridLayout* griglia;

    QTextEdit* descrizione;

    QWidget* finestra;
};

#endif // CHARTSVIEWER_H
