#include "ChartsViewer.h"
#include "AirQualityRetriever.h"

ChartsViewer::ChartsViewer(QWidget *parent): QMainWindow(parent)
{
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

    //COMPLETER COPIATO DALLA DOC
    wordList << "alpha" << "omega" << "omicron" << "zeta";

    completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    cityText->setCompleter(completer);
    //FINE COMPLETER COPIATO

    this->setWindowTitle(" ");

    connect(apriFileButton, SIGNAL(clicked()),file,SLOT(open()));

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
    dataInizio->setDate(QDate(1970,1,1));

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

    //Qui solo per ragioni di test
    AirQualityRetriever *aq = new AirQualityRetriever("7b6bde71c02400af4d2b61da7b315b31");
    //aq->retrieve(45.4079700,11.8858600);

    aq->retrieveHistorical(45.4079700, 11.8858600, QDate(2021,12,10), QDate(2021,12,12));

    connect(aq,SIGNAL(readReady(QJsonDocument*)),this,SLOT(receiveJson(QJsonDocument*)));

    resize(250,150);

    finestra = new QWidget();
    finestra->setLayout(mainCol);

    setCentralWidget(finestra);
}

//Per testare come aggiungere qualcosa al main letto da json
void ChartsViewer::receiveJson(QJsonDocument* json){
    //qDebug() << "Slot chiamato";
    if(json->isObject()){
        QJsonObject jsObj = json->object();
        QStringList chiavi = jsObj.keys();

        //QString label;

        //JSON DELLA RICHIESTA STORICA GIÀ FORMATTATO GIUSTO
        //auto value = json->toJson();

        //Non va qui ma intanto funziona
        QFile fileRichiesta("fileRichiesta.txt");
        fileRichiesta.open(QIODevice::ReadWrite);
        //qDebug() << fileRichiesta.isReadable();

        fileRichiesta.write(json->toJson());
        //QTString
        //fileRichiesta.readLine(testringa, sizeof(testringa));
        //qDebug() << "PROVAFILE" << testringa << endl;
        //fileRichiesta.close();
        //qDebug() << "value"<<value;

        //ATTUALMENTE POCO UTILE
        /*for(auto it = chiavi.begin();it < chiavi.end(); ++it){
            auto value = jsObj.take(*it);
            qDebug() << "value"<<value;
            //qDebug()<<"testdc"<<value.toObject().take("lat").toDouble();
            //qDebug()<<"testdc"<<value.toObject().take("lon").toDouble();
            //label.append(*it);
            //label.append("|");
            //qDebug()<<"tostring"<<(*jsObj.find("coord")).toObject();
        }

        //qDebug() << "stampo l'intera risposta?" << json->toJson();
        jsLabel->setText(label);
        */
    }
}

ChartsViewer::~ChartsViewer(){}
