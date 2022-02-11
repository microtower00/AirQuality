#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include "Charts/chartschooser.h"
#include "Table/tablechooser.h"

#include <QMainWindow>
#include <QGroupBox>
#include <QTextEdit>

class DataViewer : public QMainWindow
{
    Q_OBJECT

private:
    TableChooser *gbControlliTab;
    ChartsChooser *gbControlliGraf;

    QGridLayout *glMain;
    QHBoxLayout *hbGraf;
    QHBoxLayout *hbDescr;

    QGroupBox *gbDescr;
    QGroupBox *gbMostraDati;

    QLabel *lbDescr;

    MyTableView *tabella;
    MyChartView *grafico;

    QWidget *finestra;

public:
    DataViewer(Dati*, QWidget *parent = nullptr);

public slots:
   void mostraChart();
   void mostraTable();
   void setDescr(const MyChart::GraphType&);
};

#endif // DATAVIEWER_H
