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
    ChartsViewer(Dati*, QWidget *parent = nullptr);

public slots:
   void mostraChart();
   void mostraTable();
   void setDescr(const MyChart::GraphType&);
};

#endif // CHARTSVIEWER_H
