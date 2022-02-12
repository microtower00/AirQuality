#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include "Charts/chartschooser.h"
#include "Table/tablechooser.h"

#include <QGroupBox>
#include <QMainWindow>
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

    QErrorMessage *errorDialog;

    MyTableView *tabella;
    MyChartView *grafico;

    QWidget *finestra;

  public:
    DataViewer (Dati *, QWidget *parent = nullptr);

  public slots:
    void mostraChart ();
    void mostraTable ();
    void setDescr (const MyChart::GraphType &);
    void erroreDialog (const QString &);
};

#endif // DATAVIEWER_H
