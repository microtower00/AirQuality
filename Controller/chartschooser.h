#ifndef CHARTSCHOOSER_H
#define CHARTSCHOOSER_H

#include "Model/dati.h"
#include "View/mychartview.h"
#include "View/mytableview.h"

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
#include <QRadioButton>
#include <QButtonGroup>

class ChartsChooser : public QGroupBox
{
    Q_OBJECT
public:
    explicit ChartsChooser(const Dati&);

    MyChartView* getGrafico() const;
    MyTableView* getTabella() const;
public slots:
    void createChart();
    //void createTable();
    void controlliComboBox(QString);
    void selezionaTutti();
    void deselezionaTutti();
    void attivaComp(bool);

signals:

private:
    Dati data;

    QVBoxLayout* mainLayout;
    QGroupBox* sceltaGraf;
    QGridLayout* sceltaGrafLayout;
    QGroupBox *sceltaComp;

    QComboBox* grafici;

    QGridLayout* grigliaComp;

    QButtonGroup* cbComponenti;

    QRadioButton* rbComponenti;
    QRadioButton* rbAqi;

    QPushButton* pbConferma;
    QPushButton* pbTabella;
    QPushButton* pbSelTutti;
    QPushButton* pbDelTutti;

    MyChartView* grafico;
    MyTableView* tabella;
};

#endif // CHARTSCHOOSER_H
