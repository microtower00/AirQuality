#include "ChartsViewer.h"
#include "AirQualityRetriever.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QJsonObject>
#include<iostream>
#include <QCompleter>

//using namespace std;
QLabel *jsLabel;
ChartsViewer::ChartsViewer(QWidget *parent): QMainWindow(parent)
{
    QLabel *titolo = new QLabel("AirQuality Charts",this);
    QLabel *oppure = new QLabel("oppure",this);
    QLabel *inizio = new QLabel("Inizio",this);
    QLabel *fine = new QLabel("Fine",this);

    QVBoxLayout *mainCol = new QVBoxLayout();

    QHBoxLayout *rigaTitle = new QHBoxLayout();
    QHBoxLayout *rigaAzioni = new QHBoxLayout();

    QVBoxLayout *importaVbox = new QVBoxLayout();
    QVBoxLayout *openWeatherVbox = new QVBoxLayout();

    QGroupBox *importa = new QGroupBox("Apri file");
    QGroupBox *openWeather = new QGroupBox("Scarica da OpenWeather");

    QHBoxLayout *rigaDataInizio = new QHBoxLayout();
    QHBoxLayout *rigaDataFine = new QHBoxLayout();

    QPushButton *apriFileButton = new QPushButton("Importa");
    QPushButton *openWeatherButton = new QPushButton("Ottieni");
    QLineEdit *cityText = new QLineEdit();
    QDateEdit *dataInizio = new QDateEdit();
    QDateEdit *dataFine = new QDateEdit;

    QFileDialog *file = new QFileDialog(this, "Open file", "C://");

    //COMPLETER COPIATO DALLA DOC
    QStringList wordList;
    wordList << "alpha" << "omega" << "omicron" << "zeta";

    QCompleter *completer = new QCompleter(wordList, this);
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

    QWidget *finestra = new QWidget();
    finestra->setLayout(mainCol);

    setCentralWidget(finestra);
}

//Per testare come aggiungere qualcosa al main letto da json
void ChartsViewer::receiveJson(QJsonDocument* json){
    qDebug() << "Slot chiamato";
    if(json->isObject()){
        QJsonObject jsObj = json->object();
        QStringList chiavi = jsObj.keys();

        //QString label;

        //JSON DELLA RICHIESTA STORICA GIÀ FORMATTATO GIUSTO
        //auto value = json->toJson();

        //MA DIMMI TE SE UNO POI NON DEVE BESTEMMIARE NON RIESCO NÈ A LEGGERE
        //NÈ A SCRIVERE UN FILE
        /*QFile fileRichiesta("fileRichiesta.txt");
        fileRichiesta.open(QIODevice::ReadWrite);
        qDebug() << fileRichiesta.isReadable();

        fileRichiesta.write("ciao ragazzi ciao a tutti sono zeb89");
        char testringa[64];
        fileRichiesta.readLine(testringa, sizeof(testringa));
        qDebug() << "PROVAFILE" << testringa << endl;
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
