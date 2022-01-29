#include "chartschooser.h"

ChartsChooser::ChartsChooser(const Dati& graf, QWidget* parent) : QMainWindow(parent), data(graf)
{
    mainLayout = new QVBoxLayout();

    sceltaGraf = new QGroupBox("Scegli il tipo di grafico");

    grafici = new QComboBox();
    grafici->addItem("A linee");
    grafici->addItem("Istogramma");
    grafici->addItem("Plot");
    grafici->addItem("Radar");

    grafico = new MyChartView();

    area = new QCheckBox("Aree");
    area->setDisabled(true);

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

    //non avevo voglia di iterare, che vergogna
    grigliaComp->addWidget(cbComponenti[0], 0, 0);
    grigliaComp->addWidget(cbComponenti[1], 0, 1);
    grigliaComp->addWidget(cbComponenti[2], 0, 2);
    grigliaComp->addWidget(cbComponenti[3], 0, 3);
    grigliaComp->addWidget(cbComponenti[4], 1, 0);
    grigliaComp->addWidget(cbComponenti[5], 1, 1);
    grigliaComp->addWidget(cbComponenti[6], 1, 2);
    grigliaComp->addWidget(cbComponenti[7], 1, 3);

    sceltaComp->setLayout(grigliaComp);

    conferma = new QPushButton("Conferma");

    mainLayout->addWidget(sceltaGraf);
    mainLayout->addWidget(sceltaComp);
    mainLayout->addWidget(conferma);

    finestra = new QWidget();
    finestra->setLayout(mainLayout);

    setCentralWidget(finestra);

    connect(conferma,SIGNAL(clicked()),this,SLOT(displayChart()));

    /*testLab = new QLabel("Scegli il tipo di grafico:");
    bottLinee = new QPushButton("A linee");
    bottArea = new QPushButton("Ad area");
    bottIsto = new QPushButton("Istogramma");
    bottPlot = new QPushButton("Plot");
    bottRadar = new QPushButton("Radar");
    grafico = new MyChartView();
    //scrollA = new QScrollArea();

    QStringList listaComp = data.getChiavi();
    listaComp.removeFirst();
    componenti = new QComboBox();
    componenti->addItems(listaComp);

    gridCharts = new QGridLayout;

    //resize(1000,600);

    testFin = new QWidget();
    testFin->setLayout(gridCharts);

    gridCharts->addWidget(testLab, 0, 0, 1, 2);
    gridCharts->addWidget(bottLinee, 1, 0, 1, 1);
    gridCharts->addWidget(componenti, 1, 1, 1, 1);
    gridCharts->addWidget(bottArea, 2, 0, 1, 1);
    gridCharts->addWidget(bottIsto, 2, 1, 1, 1);
    gridCharts->addWidget(bottPlot, 3, 0, 1, 1);
    gridCharts->addWidget(bottRadar, 3, 1, 1, 1);

    // abbandono momentaneamente l'idea di rendere scrollabili grafici perchè
    // gestire sta cosa mi fa bestemmiare
    grafico->setMinimumSize(1000,800);
    qDebug()<<grafico->sizeHint();
    grafico->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    //grafico->setMaximumSize(1000000,800);
    scrollA->setWidget(grafico);
    gridCharts->addWidget(scrollA);

    setCentralWidget(testFin);
    connect(bottLinee,SIGNAL(clicked()),this,SLOT(displayLineChart()));
    connect(bottIsto,SIGNAL(clicked()),this,SLOT(displayBarChart()));
    connect(bottRadar,SIGNAL(clicked()),this,SLOT(displayRadarChart()));
    connect(bottArea,SIGNAL(clicked()),this,SLOT(displayAreaChart()));*/
}

void ChartsChooser::displayChart(){
    QStringList compScelti;

    for(auto it:cbComponenti)
        if(it->isChecked())
            compScelti.push_back(it->text());

    if(grafici->currentText()=="A linee")
        grafico->lineChart(data, compScelti);
    else if(grafici->currentText()=="Istogramma")
        grafico->barChart(data, compScelti);
    else if(grafici->currentText()=="Radar")
        grafico->radarChart(data, compScelti);
}


