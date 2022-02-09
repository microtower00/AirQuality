#ifndef CHARTSVIEWER_H
#define CHARTSVIEWER_H

#include "chartschooser.h"
#include "tablechooser.h"

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
   void setDescr(const MyChart::GraphType&);
   //void iniziaSalvataggio();

signals:

private:
    QHBoxLayout* layoutGraf;
    QHBoxLayout* layoutDescr;
    QGridLayout* griglia;

    ChartsChooser* GBcontrolliG;
    TableChooser* GBcontrolliT;
    QGroupBox* GBdescrizione;
    QGroupBox* GBmostraDati;

    QLabel* descrizione;

    MyTableView* tabella;
    MyChartView* grafico;

    QWidget* finestra;
};

#endif // CHARTSVIEWER_H
