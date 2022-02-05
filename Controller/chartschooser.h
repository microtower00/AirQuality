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
#include <QRadioButton>

class ChartsChooser : public QGroupBox
{
    Q_OBJECT
public:
    explicit ChartsChooser(const Dati&);

    MyChartView* getGrafico() const;
public slots:
    void createChart();
    void attivaArea(QString);
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
    QCheckBox* area;

    QGridLayout* grigliaComp;

    QList<QCheckBox*> cbComponenti;

    QRadioButton* rbComponenti;
    QRadioButton* rbAqi;

    QPushButton* conferma;
    QPushButton* selTutti;
    QPushButton* delTutti;

    MyChartView* grafico;
};

#endif // CHARTSCHOOSER_H
