//DEPRECATA
#include "chartsviewer.h"

ChartsViewer::ChartsViewer(QWidget *parent):
    QMainWindow(parent)
{
    qDebug()<<"Costruisco chartsviewer";
    titolo = new QLabel("AirQuality Charts",this);
    oppure = new QLabel("oppure",this);
    inizio = new QLabel("Inizio",this);
    fine = new QLabel("Fine",this);
    erroreDateLab = new QLabel();
    erroreCityLab = new QLabel();

    mainCol = new QVBoxLayout();

    rigaTitle = new QHBoxLayout();
    rigaAzioni = new QHBoxLayout();

    importaVbox = new QVBoxLayout();
    openWeatherVbox = new QVBoxLayout();

    importa = new QGroupBox("Apri file");
    openWeather = new QGroupBox("Scarica da internet");

    rigaDataInizio = new QHBoxLayout();
    rigaDataFine = new QHBoxLayout();

    apriFileButton = new QPushButton("Importa");
    openWeatherButton = new QPushButton("Ottieni");
    bottoneCambio = new QPushButton("Cambia finestra");
    cityText = new QLineEdit();
    dataInizio = new QDateEdit();
    dataFine = new QDateEdit;


    file = new QFileDialog(this, "Open file", "C://");


    this->setWindowTitle("AirQuality Charts");

    rigaAzioni->setAlignment(Qt::AlignHCenter);
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

    erroreDateLab->setVisible(false);
    openWeatherVbox->addWidget(erroreDateLab);

    erroreCityLab->setVisible(false);
    openWeatherVbox->addWidget(erroreCityLab);

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
    //data = new dataviewer;
    //-->connect(model, SIGNAL(savedObj(QJsonObject)), data, SLOT(createTable(QJsonObject)));

    //Chiama la gestione per aprire il file dialog quando si preme Importa
    connect(apriFileButton, SIGNAL(clicked()),this,SLOT(cliccatoImporta()));
    resize(250,150);

    finestra = new QWidget();
    finestra->setLayout(mainCol);

    setCentralWidget(finestra);
}

//DEPRECATO
void ChartsViewer::bottoneOttieni(){
    emit needDati(cityText->text(),dataInizio->date(),dataFine->date());

    try {
        erroreDateLab->setVisible(false);
        erroreCityLab->setVisible(false);
        //Al momento questa parte é codice morto------|
        //                                            V
    } catch(std::domain_error) {
        erroreCityLab->setText("<body style='color: red'>Errore nella città</body>");
        erroreCityLab->setVisible(true);
        //qDebug()<<"catchata";
    } catch(std::invalid_argument) {
        erroreDateLab->setText("<body style='color: red'>Errore nelle date</body>");
        erroreDateLab->setVisible(true);
    }
}

//DEPRECATO
void ChartsViewer::cliccatoImporta(){
    //-->model->openFileDialog(this);
}

//DEPRECATO
void ChartsViewer::setCompleterList(QStringList listaCitta){
    completer=new QCompleter(listaCitta);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    cityText->setCompleter(completer);
}

ChartsViewer::~ChartsViewer(){}
