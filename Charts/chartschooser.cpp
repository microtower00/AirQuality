#include "chartschooser.h"

ChartsChooser::ChartsChooser (Dati *dati)
    : data (dati), grafico (new MyChartView (data))
{
    QStringList listaComp = data->getChiavi ();
    listaComp.removeFirst ();
    listaComp.removeLast ();

    vbMainLayout = new QVBoxLayout ();
    glSceltaGraf = new QGridLayout ();
    glComp = new QGridLayout ();

    gbSceltaGraf = new QGroupBox ("Scegli il tipo di grafico");
    gbSceltaComp = new QGroupBox ("Scegli i componenti");

    cbGrafici = new QComboBox ();

    cbComponenti = new QButtonGroup ();

    rbComponenti = new QRadioButton ("Componenti");
    rbAqi = new QRadioButton ("Qualità dell'aria");

    pbConferma = new QPushButton ("Visualizza grafico");
    pbSelTutti = new QPushButton ("Seleziona tutti");
    pbDelTutti = new QPushButton ("Deseleziona tutti");

    cbGrafici->addItem ("A linee");
    cbGrafici->addItem ("Ad aree");
    cbGrafici->addItem ("Istogramma");
    cbGrafici->addItem ("Plot");
    cbGrafici->addItem ("Radar");

    rbComponenti->setChecked (true);

    cbComponenti->setExclusive (false);

    gbSceltaComp->setVisible (rbComponenti->isChecked ());

    glSceltaGraf->addWidget (rbComponenti, 0, 0);
    glSceltaGraf->addWidget (rbAqi, 0, 1);
    glSceltaGraf->addWidget (cbGrafici, 1, 0);

    for (auto comp : listaComp)
        {
            cbComponenti->addButton (new QCheckBox (comp));
            glComp->addWidget (
                cbComponenti->buttons ().at (listaComp.indexOf (comp)),
                listaComp.indexOf (comp) / 4, listaComp.indexOf (comp) % 4);
        }
    glComp->addWidget (pbSelTutti, 2, 0, 2, 2);
    glComp->addWidget (pbDelTutti, 2, 2, 2, 2);

    gbSceltaGraf->setLayout (glSceltaGraf);
    gbSceltaComp->setLayout (glComp);
    vbMainLayout->addWidget (gbSceltaGraf);
    vbMainLayout->addWidget (gbSceltaComp);
    vbMainLayout->addWidget (pbConferma);

    this->setLayout (vbMainLayout);

    setTitle ("Controlli grafici");
    setFixedWidth (300);
    setFixedHeight (325);
    setSizePolicy (QSizePolicy (QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect (rbComponenti, SIGNAL (toggled (bool)), this,
             SLOT (attivaComp (bool)));
    connect (cbGrafici, SIGNAL (currentTextChanged (QString)), this,
             SLOT (controlliComboBox (QString)));
    connect (pbSelTutti, SIGNAL (clicked ()), this, SLOT (selezionaTutti ()));
    connect (pbDelTutti, SIGNAL (clicked ()), this, SLOT (deselezionaTutti ()));
    connect (pbConferma, SIGNAL (clicked ()), this, SLOT (createChart ()));
}

void
ChartsChooser::controlliComboBox (const QString &testoCBgrafici)
{
    cbComponenti->setExclusive (testoCBgrafici == "Plot");
    pbSelTutti->setDisabled (testoCBgrafici == "Plot");

    if (testoCBgrafici == "Plot")
        pbDelTutti->click ();

    emit comboChanged (MyChart::stringToEnum (testoCBgrafici));
}

void
ChartsChooser::createChart ()
{
    QStringList compScelti = QStringList ();

    if (rbComponenti->isChecked ())
        {
            for (auto cbComp : cbComponenti->buttons ())
                if (cbComp->isChecked ())
                    compScelti.push_back (cbComp->text ());

            if (!compScelti.isEmpty ())
                {
                    grafico->setCompScelti (compScelti);

                    if (cbGrafici->currentText () == "A linee")
                        grafico->lineChart ();
                    else if (cbGrafici->currentText () == "Ad aree")
                        grafico->areaChart ();
                    else if (cbGrafici->currentText () == "Istogramma")
                        grafico->barChart ();
                    else if (cbGrafici->currentText () == "Radar")
                        {
                            if (compScelti.size () >= 3)
                                grafico->radarChart ();
                            else
                                emit erroreGraf ("Inserire almeno 3 componenti "
                                                 "per il grafico radar.");
                        }
                    else if (cbGrafici->currentText () == "Plot")
                        grafico->scatterChart ();

                    emit chartCreated ();
                }
            else
                emit erroreGraf ("Inserire almeno uno o più componenti.");
        }
    else if (rbAqi->isChecked ())
        {
            compScelti.push_back ("aqi");
            grafico->setCompScelti (compScelti);
            grafico->lineChart ();
            emit chartCreated ();
        }
}

void
ChartsChooser::selezionaTutti ()
{
    for (auto cbComp : cbComponenti->buttons ())
        cbComp->setChecked (true);
}

void
ChartsChooser::deselezionaTutti ()
{
    for (auto cbComp : cbComponenti->buttons ())
        cbComp->setChecked (false);
}

MyChartView *
ChartsChooser::getGrafico () const
{
    return grafico;
}

void
ChartsChooser::attivaComp (const bool &compChecked)
{
    gbSceltaComp->setEnabled (compChecked);

    if (!compChecked)
        {
            cbGrafici->setCurrentIndex (0);
            for (int i = 1; i < cbGrafici->count (); ++i)
                cbGrafici->setItemData (i, 0, Qt::UserRole - 1);
        }
    else
        {
            for (int i = 1; i < cbGrafici->count (); ++i)
                cbGrafici->setItemData (i, 33, Qt::UserRole - 1);
        }
}
