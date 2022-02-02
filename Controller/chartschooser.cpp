#include "chartschooser.h"

ChartsChooser::ChartsChooser(const Dati& graf) :  data(graf)
{
    mainLayout = new QVBoxLayout();

    sceltaGraf = new QGroupBox("Scegli il tipo di grafico");

    grafici = new QComboBox();
    grafici->addItem("A linee");
    grafici->addItem("Istogramma");
    grafici->addItem("Plot");
    grafici->addItem("Radar");

    area = new QCheckBox("Aree");
    area->setDisabled(!(grafici->currentText()=="A linee"));

    sceltaGrafLayout = new QHBoxLayout();
    sceltaGrafLayout->addWidget(grafici);
    sceltaGrafLayout->addWidget(area);

    sceltaGraf->setLayout(sceltaGrafLayout);

    sceltaComp = new QGroupBox("Scegli i componenti");

    QStringList listaComp = data.getChiavi();
    listaComp.removeFirst();
    listaComp.removeLast();

    for(auto it:listaComp)
        cbComponenti.push_back(new QCheckBox(it));

    grigliaComp = new QGridLayout();

    selTutti = new QPushButton("Seleziona tutti");
    delTutti = new QPushButton("Deseleziona tutti");

    //non avevo voglia di iterare, che vergogna
    grigliaComp->addWidget(cbComponenti[0], 0, 0);
    grigliaComp->addWidget(cbComponenti[1], 0, 1);
    grigliaComp->addWidget(cbComponenti[2], 0, 2);
    grigliaComp->addWidget(cbComponenti[3], 0, 3);
    grigliaComp->addWidget(cbComponenti[4], 1, 0);
    grigliaComp->addWidget(cbComponenti[5], 1, 1);
    grigliaComp->addWidget(cbComponenti[6], 1, 2);
    grigliaComp->addWidget(cbComponenti[7], 1, 3);
    grigliaComp->addWidget(selTutti, 2, 0, 2, 2);
    grigliaComp->addWidget(delTutti, 2, 2, 2, 2);

    sceltaComp->setLayout(grigliaComp);

    conferma = new QPushButton("Conferma");

    mainLayout->addWidget(sceltaGraf);
    mainLayout->addWidget(sceltaComp);
    mainLayout->addWidget(conferma);

    this->setLayout(mainLayout);

    grafico = new MyChartView(data);

    setTitle("Controlli");
    setMaximumWidth(640);
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    connect(grafici,SIGNAL(currentTextChanged(QString)),this,SLOT(attivaArea(QString)));
    connect(selTutti,SIGNAL(clicked()),this,SLOT(selezionaTutti()));
    connect(delTutti,SIGNAL(clicked()),this,SLOT(deselezionaTutti()));
    connect(conferma,SIGNAL(clicked()),this,SLOT(createChart()));
}

void ChartsChooser::attivaArea(QString testoCBgrafici) {
    area->setEnabled(testoCBgrafici=="A linee");
}

void ChartsChooser::createChart(){

    QStringList compScelti = QStringList();

    for(auto cbComp:cbComponenti)
        if(cbComp->isChecked())
            compScelti.push_back(cbComp->text());

    if(!compScelti.isEmpty()) {
        grafico->setCompScelti(compScelti);

        if(grafici->currentText()=="A linee")
            area->isChecked() ? grafico->areaChart() : grafico->lineChart();
        else if(grafici->currentText()=="Istogramma")
            grafico->barChart();
        else if(grafici->currentText()=="Radar")
            grafico->radarChart();
        else if(grafici->currentText()=="Plot")
            grafico->scatterChart();

        //resize(width()+1250, 750);

        conferma->setText("Aggiorna");
    }
}

void ChartsChooser::selezionaTutti() {
    for(auto cbComp:cbComponenti)
        cbComp->setChecked(true);
}

void ChartsChooser::deselezionaTutti() {
    for(auto cbComp:cbComponenti)
        cbComp->setChecked(false);
}

MyChartView* ChartsChooser::getGrafico() const {
    return grafico;
}




