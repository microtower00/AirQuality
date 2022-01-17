#include "startwindow.h"

const QString StartWindow::APIKEY = "7b6bde71c02400af4d2b61da7b315b31";

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow{parent}
{
    qDebug()<<"StartWindow::StartWindow()";

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

    this->setWindowTitle("AirQuality Charts");

    rigaAzioni->setAlignment(Qt::AlignHCenter);
    mainCol->setSpacing(30);

    QFont ubuntuF("Ubuntu Thin", 24);
    titolo->setFont(ubuntuF);

    cityText->setPlaceholderText("Inserisci città");
    cityText->setMinimumSize(200,27);
    cityText->setCompleter(createCompleter());

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

    finestra = new QWidget();
    finestra->setLayout(mainCol);

    resize(250,150);
    setCentralWidget(finestra);



    //connect(this, SIGNAL(savedObj(QJsonObject)), data, SLOT(createTable(QJsonObject)));

    connect(this,SIGNAL(filePronto(const QJsonDocument*)),this,SLOT(creoModel(const QJsonDocument*)));
    //connect(this,SIGNAL(filePronto(const QJsonDocument*)),this,SLOT(saveJSonReply(const QJsonDocument*)));
    connect(&aqr,SIGNAL(readReady(const QJsonDocument*)),this,SLOT(creoModel(const QJsonDocument*)));
    connect(apriFileButton,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(openWeatherButton,SIGNAL(clicked()),this,SLOT(getAirQuality()));

    qDebug()<<"Sto per crashare";
    connect(this, SIGNAL(modelCreato(const Dati&)), this, SLOT(apriSelettore(const Dati&)));
    //data = new DataViewer;
    //connect(this, SIGNAL(modelCreato(Dati)), data, SLOT(createTable(Dati)));
}

//decidere che fare se file scelto é nullo
void StartWindow::chooseFile(){
    QString fileName = QFileDialog::getOpenFileName(this, "Scegli un file grafico","","File JSON (*.json)");
    if(fileName!=NULL)
        //creare il modello
        emit filePronto(&openJson(fileName));
}

void StartWindow::getAirQuality(){
    cityText->text().isNull() ? qDebug()<<"null" : qDebug()<<"OK";
    QDate fine = dataFine->date();
    QDate inizio = dataInizio->date();
    QGeoCoordinate coords_citta = coordsResolver(cityText->text());
    qDebug() << "FPickerController::getAirQuality()";

    QDate primadataDisp = primadataDisp.fromString("2020-11-27", Qt::ISODate);

    if(inizio>=primadataDisp && fine<=QDate::currentDate() && fine>inizio)
        aqr.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
    else throw std::invalid_argument("Date non valide");
}

QGeoCoordinate StartWindow::coordsResolver(QString citta) const{
    QJsonObject json_obj;

    QJsonArray json_array = getCitiesJson().array();

    //cerco in tutto l'array
    for(int i=0; i< json_array.count(); ++i){
        json_obj = json_array.at(i).toObject();
        if(json_obj["city_ascii"]==citta){
            return QGeoCoordinate(json_obj["lat"].toDouble(),json_obj["lng"].toDouble());
        }
    }
    throw std::domain_error("La città inserita non è disponibile");
}

QJsonDocument& StartWindow::getCitiesJson() const {

    QJsonDocument* json = new QJsonDocument(openJson("worldcities.json"));

    if(!json->isArray())
        throw std::invalid_argument("Il file che si sta cercando di aprire non contiene un JSON");

    QJsonArray json_array = json->array();

    if(json_array.isEmpty())
        qDebug() << "L'array è vuoto";

    return *json;
}

QCompleter* StartWindow::createCompleter() const{
    QStringList listaCitta;
    QJsonArray json_array = getCitiesJson().array();

    //cerco in tutto l'array
    for(int i=0; i<json_array.count(); ++i)
        listaCitta.append(json_array.at(i).toObject()["city_ascii"].toString());

    QCompleter* citylist = new QCompleter(listaCitta);
    citylist->setCaseSensitivity(Qt::CaseInsensitive);
    return citylist;
}

void StartWindow::creoModel(const QJsonDocument* datiDoc) {
    Dati dati(datiDoc->object());
    qDebug()<<"StartWindow::creoModel(const QJsonDocument*)";
    emit modelCreato(dati);
}

QJsonDocument& StartWindow::openJson(QString relativePath) const{
    QString val;
    QFile file;

    file.setFileName(relativePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument* json = new QJsonDocument(QJsonDocument::fromJson(val.toLocal8Bit()));
    if(json->isNull())
        throw std::invalid_argument("Il file che si sta cercando di aprire non é valido");
    return *json;
}

//Fa la chiamata al retriever. Non ritorna nulla perché i valori di ritorno vengono gestiti dal segnale readReady, connesso a saveJSonReply
void StartWindow::ottieniDati(QString citta, QDate inizio, QDate fine) const{
    //senza la riga sottostante crasha se non viene messa la città, non ha nessun senso
    citta.isNull() ? qDebug()<<"null" : qDebug()<<"OK";
    QGeoCoordinate coords_citta = coordsResolver(citta);
    qDebug() << "Model::ottieniDati(QString,QDate,QDate)";

    QDate inizioAPI = inizioAPI.fromString("2020-11-27", Qt::ISODate);

    if(inizio>=inizioAPI && fine<=QDate::currentDate() && fine>inizio)
        aqr.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
    else throw std::invalid_argument("Date non valide");
}

//Salva un oggetto QJSonDocument come file JSon, ed emette il segnale savedFile
void StartWindow::saveJSonReply(const QJsonDocument* doc) const{
    qDebug() << "Model::saveJSonReply(QJsonDocument*)";
    if(doc->isObject()){
        QJsonObject jsObj = doc->object();
        //commentato perchè non in uso
        //QStringList chiavi = jsObj.keys();
        qDebug()<< "filename: "<< QDateTime::currentDateTimeUtc().toString(Qt::ISODate);

        QString filename= QString(QDateTime::currentDateTimeUtc().toString(Qt::ISODate)).append(".json");

        QFile fileRichiesta(filename);
        fileRichiesta.open(QIODevice::ReadWrite);

        fileRichiesta.write(doc->toJson());
        fileRichiesta.close();

        //segnale aggiunto per comodita nella creazione della tabella
        //emit savedObj(jsObj);
        //emit savedFile(QCoreApplication::applicationDirPath()+filename);
    }
}

void StartWindow::apriSelettore(const Dati& d){
    selettore = new ChartsChooser(d);
    selettore->show();
}


