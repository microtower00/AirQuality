#include "chartsviewer.h"

ChartsViewer::ChartsViewer(QWidget *parent):
    QMainWindow(parent)
{
    model = new Model("7b6bde71c02400af4d2b61da7b315b31");
    titolo = new QLabel("AirQuality Charts",this);
    oppure = new QLabel("oppure",this);
    inizio = new QLabel("Inizio",this);
    fine = new QLabel("Fine",this);

    mainCol = new QVBoxLayout();

    rigaTitle = new QHBoxLayout();
    rigaAzioni = new QHBoxLayout();

    importaVbox = new QVBoxLayout();
    openWeatherVbox = new QVBoxLayout();

    importa = new QGroupBox("Apri file");
    openWeather = new QGroupBox("Scarica da OpenWeather");

    rigaDataInizio = new QHBoxLayout();
    rigaDataFine = new QHBoxLayout();

    apriFileButton = new QPushButton("Importa");
    openWeatherButton = new QPushButton("Ottieni");
    bottoneCambio = new QPushButton("Cambia finestra");
    cityText = new QLineEdit();
    dataInizio = new QDateEdit();
    dataFine = new QDateEdit;


    file = new QFileDialog(this, "Open file", "C://");

    completer = new QCompleter(model->getCompleterList(), this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    cityText->setCompleter(completer);

    this->setWindowTitle(" ");


    rigaAzioni->setAlignment(Qt::AlignHCenter);
    //rigaTitle->setAlignment(Qt::AlignHCenter);
    mainCol->setSpacing(30);

    QFont ubuntuF("Ubuntu Thin", 24);
    titolo->setFont(ubuntuF);

    cityText->setPlaceholderText("Inserisci città");
    cityText->setMinimumSize(200,27);

    dataInizio->setMinimumSize(150,27);
    dataFine->setMinimumSize(150,27);

    dataFine->setDate(QDate::currentDate());
    dataInizio->setDate(QDate(2020,11,27));

    rigaTitle->addWidget(titolo);
    mainCol->addLayout(rigaTitle);

    importaVbox->addWidget(apriFileButton);
    importa->setLayout(importaVbox);
    rigaAzioni->addWidget(importa);
    mainCol->addLayout(rigaAzioni);

    rigaAzioni->addWidget(oppure);

    openWeatherVbox->addWidget(cityText);
    rigaDataInizio->addWidget(inizio);
    rigaDataInizio->addWidget(dataInizio);

    openWeatherVbox->addLayout(rigaDataInizio);
    rigaDataFine->addWidget(fine);
    rigaDataFine->addWidget(dataFine);

    openWeatherVbox->addLayout(rigaDataFine);
    openWeatherVbox->addWidget(openWeatherButton);
    openWeather->setLayout(openWeatherVbox);
    rigaAzioni->addWidget(openWeather);
    mainCol->addLayout(rigaAzioni);

    jsLabel = new QLabel("");
    mainCol->addWidget(jsLabel);

    charts = new ChartsChoser;
    //connect(testNewWindow, SIGNAL(clicked()),c,SLOT(show()));
    //connect(testNewWindow, SIGNAL(clicked()),this,SLOT(hide()));
    //qua sotto provo a far riapparire questa finestra alla chiusura di chooser ma senza successo
    //connect(c, SIGNAL(exit()),this,SLOT(show()));


    //Quando premi, salva un file che contiene il json dell'intervallo selezionato
    connect(openWeatherButton,SIGNAL(clicked()),this,SLOT(bottoneOttieni()));

    //Una volta che il file é stato salvato, apre la nuova finestra che ne mostra i dati
    data = new dataviewer;
    connect(model, SIGNAL(savedObj(QJsonObject)), data, SLOT(createTable(QJsonObject)));

    //Chiama la gestione per aprire il file dialog quando si preme Importa
    connect(apriFileButton, SIGNAL(clicked()),this,SLOT(cliccatoImporta()));
    resize(250,150);

    finestra = new QWidget();
    finestra->setLayout(mainCol);

    setCentralWidget(finestra);
}

void ChartsViewer::bottoneOttieni(){
    //qDebug()<< "Data inizio: "<< dataInizio->date()<<",Data fine: "<<dataFine->date();
    model->ottieniDati(cityText->text(),dataInizio->date(),dataFine->date());
}

void ChartsViewer::cliccatoImporta(){
    model->openFileDialog(this);
}
ChartsViewer::~ChartsViewer(){}
