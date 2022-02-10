#include "chartschooser.h"

ChartsChooser::ChartsChooser(const Dati& dati) :  data(dati)
{

    mainLayout = new QVBoxLayout();

    sceltaGraf = new QGroupBox("Scegli il tipo di grafico");

    grafici = new QComboBox();
    grafici->addItem("A linee");
    grafici->addItem("Ad aree");
    grafici->addItem("Istogramma");
    grafici->addItem("Plot");
    grafici->addItem("Radar");

    rbComponenti = new QRadioButton("Componenti");
    rbComponenti->setChecked(true);
    rbAqi = new QRadioButton("Qualità dell'aria");

    sceltaGrafLayout = new QGridLayout();
    sceltaGrafLayout->addWidget(grafici, 0, 0);
    sceltaGrafLayout->addWidget(rbComponenti, 1, 0);
    sceltaGrafLayout->addWidget(rbAqi, 1, 1);

    sceltaGraf->setLayout(sceltaGrafLayout);

    sceltaComp = new QGroupBox("Scegli i componenti");

    QStringList listaComp = data.getChiavi();

    listaComp.removeFirst();
    listaComp.removeLast();

    cbComponenti = new QButtonGroup();
    cbComponenti->setExclusive(false);

    for(auto it:listaComp)
        cbComponenti->addButton(new QCheckBox(it));

    grigliaComp = new QGridLayout();

    pbSelTutti = new QPushButton("Seleziona tutti");
    pbDelTutti = new QPushButton("Deseleziona tutti");

    //non avevo voglia di iterare, che vergogna
    grigliaComp->addWidget(cbComponenti->buttons().at(0), 0, 0);
    grigliaComp->addWidget(cbComponenti->buttons().at(1), 0, 1);
    grigliaComp->addWidget(cbComponenti->buttons().at(2), 0, 2);
    grigliaComp->addWidget(cbComponenti->buttons().at(3), 0, 3);
    grigliaComp->addWidget(cbComponenti->buttons().at(4), 1, 0);
    grigliaComp->addWidget(cbComponenti->buttons().at(5), 1, 1);
    grigliaComp->addWidget(cbComponenti->buttons().at(6), 1, 2);
    grigliaComp->addWidget(cbComponenti->buttons().at(7), 1, 3);
    grigliaComp->addWidget(pbSelTutti, 2, 0, 2, 2);
    grigliaComp->addWidget(pbDelTutti, 2, 2, 2, 2);

    sceltaComp->setLayout(grigliaComp);
    sceltaComp->setVisible(rbComponenti->isChecked());

    pbConferma = new QPushButton("Visualizza grafico");

    mainLayout->addWidget(sceltaGraf);
    mainLayout->addWidget(sceltaComp);
    mainLayout->addWidget(pbConferma);
    //mainLayout->addWidget(pbTabella);
    //mainLayout->addWidget(salvaFile);


    this->setLayout(mainLayout);
    grafico = new MyChartView(data);
    //tabella = new MyTableView(data);

    //qDebug()<<nativeParentWidget()->width();

    setTitle("Controlli grafici");
    //setMaximumWidth(640);
    setFixedWidth(300);
    setFixedHeight(350);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(rbComponenti,SIGNAL(toggled(bool)),this,SLOT(attivaComp(bool)));
    connect(grafici,SIGNAL(currentTextChanged(QString)),this,SLOT(controlliComboBox(QString)));
    connect(pbSelTutti,SIGNAL(clicked()),this,SLOT(selezionaTutti()));
    connect(pbDelTutti,SIGNAL(clicked()),this,SLOT(deselezionaTutti()));
    connect(pbConferma,SIGNAL(clicked()),this,SLOT(createChart()));
}

void ChartsChooser::controlliComboBox(QString testoCBgrafici) {
    cbComponenti->setExclusive(testoCBgrafici=="Plot");
    pbSelTutti->setDisabled(testoCBgrafici=="Plot");

    if(testoCBgrafici=="Plot") pbDelTutti->click();
}

void ChartsChooser::createChart(){
    QStringList compScelti = QStringList();

    if(rbComponenti->isChecked()) {
        for(auto cbComp:cbComponenti->buttons())
            if(cbComp->isChecked())
                compScelti.push_back(cbComp->text());

        if(!compScelti.isEmpty()) {
            grafico->setCompScelti(compScelti);

            if(grafici->currentText()=="A linee")
                grafico->lineChart();
            else if(grafici->currentText()=="Ad aree")
                grafico->areaChart();
            else if(grafici->currentText()=="Istogramma")
                grafico->barChart();
            else if(grafici->currentText()=="Radar" && compScelti.size()>=3)
                grafico->radarChart();
            else if(grafici->currentText()=="Plot")
                grafico->scatterChart();

            pbConferma->setText("Aggiorna grafico");
        }
    } else if(rbAqi->isChecked()) {
        compScelti.push_back("aqi");
        grafico->setCompScelti(compScelti);
        grafico->lineChart();

        pbConferma->setText("Aggiorna grafico");
    }
}

/*MyTableView* ChartsChooser::getTabella() const{
    return tabella;
}*/

void ChartsChooser::selezionaTutti() {
    for(auto cbComp:cbComponenti->buttons())
        cbComp->setChecked(true);
}

void ChartsChooser::deselezionaTutti() {
    for(auto cbComp:cbComponenti->buttons())
        cbComp->setChecked(false);
}

MyChartView* ChartsChooser::getGrafico() const {
    return grafico;
}

void ChartsChooser::attivaComp(bool compChecked) {
    sceltaComp->setEnabled(compChecked);

    if(!compChecked) {
        grafici->setCurrentIndex(0);
        for(unsigned int i=1; i<grafici->count(); ++i)
            grafici->setItemData(i, 0,  Qt::UserRole -1);
    } else {
        for(unsigned int i=1; i<grafici->count(); ++i)
            grafici->setItemData(i, 33,  Qt::UserRole -1);
    }
}
