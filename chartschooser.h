#ifndef CHARTSCHOOSER_H
#define CHARTSCHOOSER_H

#include "dati.h"
#include "mychartview.h"

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QDateTimeAxis>
#include <QSizePolicy>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFileDialog>

class ChartsChooser : public QGroupBox
{
    Q_OBJECT

private:
    Dati* data;
    MyChartView *grafico;

    QVBoxLayout *vbMainLayout;
    QGridLayout *glComp;
    QGridLayout *glSceltaGraf;

    QGroupBox *gbSceltaGraf;
    QGroupBox *gbSceltaComp;

    QComboBox *cbGrafici;

    QButtonGroup *cbComponenti;

    QRadioButton *rbComponenti;
    QRadioButton *rbAqi;

    QPushButton *pbConferma;
    QPushButton *pbSelTutti;
    QPushButton *pbDelTutti;

public:
    explicit ChartsChooser(Dati*);
    MyChartView* getGrafico() const;

public slots:
    void createChart();
    void controlliComboBox(const QString&);
    void selezionaTutti();
    void deselezionaTutti();
    void attivaComp(const bool&);
};

#endif // CHARTSCHOOSER_H
