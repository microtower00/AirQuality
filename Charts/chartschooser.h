#ifndef CHARTSCHOOSER_H
#define CHARTSCHOOSER_H

#include "Model/dati.h"
#include "mychartview.h"

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeAxis>
#include <QErrorMessage>
#include <QFileDialog>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QSizePolicy>

class ChartsChooser : public QGroupBox
{
    Q_OBJECT

  private:
    Dati *data;
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
    explicit ChartsChooser (Dati *);
    MyChartView *getGrafico () const;

  public slots:
    void createChart ();
    void controlliComboBox (const QString &);
    void selezionaTutti ();
    void deselezionaTutti ();
    void attivaComp (const bool &);

  signals:
    void comboChanged (const MyChart::GraphType &);
    void chartCreated ();
    void erroreGraf (const QString &);
};

#endif // CHARTSCHOOSER_H
