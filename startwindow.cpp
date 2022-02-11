#include "startwindow.h"

const QString StartWindow::APIKEY = "7b6bde71c02400af4d2b61da7b315b31";
QString StartWindow::fileNonValido = "Il file che stai cercando di aprire non è supportato.";
QString StartWindow::cittaNonPresente = "La città inserita è vuota o non riconosciuta.";
QString StartWindow::dateNonCorrette = "Le date inserite non sono valide.";

StartWindow::StartWindow(QWidget *parent) : QMainWindow{parent}
{
    // Inizializzazione layout
    grLayout = new QGridLayout(this);
    vbImporta = new QVBoxLayout(this);
    vbOnline = new QVBoxLayout(this);
    hbDataInizio = new QHBoxLayout(this);
    hbDataFine = new QHBoxLayout(this);

    // Inizializzazione QGroupBox
    gbFile = new QGroupBox("File");
    gbOnline = new QGroupBox("Scarica da internet");

    // Inizializzazione label
    lbTitolo = new QLabel("AirQuality Charts",this);
    lbOppure = new QLabel("oppure",this);
    lbInizio = new QLabel("Inizio",this);
    lbFine = new QLabel("Fine",this);
    lbErrore = new QLabel(this);

    // Inizializzazione campi di testo/data
    leCity = new CittaEdit("Inserisci città",this);
    dtInizio = new QDateEdit();
    dtFine = new QDateEdit;

    // Inizializzazione QPushButton
    pbImporta = new QPushButton("Importa",this);
    pbOttieni = new QPushButton("Ottieni",this);
    pbCrea = new QPushButton("Crea nuovo",this);

    // Formattazione titolo
    QFont ubuntuF("Ubuntu Thin", 24);
    lbTitolo->setFont(ubuntuF);

    // Messaggi di errore non visibili inizialmente
    lbErrore->setVisible(false);

    // Setting campi date
    dtInizio->setMinimumSize(150,27);
    dtInizio->setDate(QDate(2020,11,27));
    dtFine->setMinimumSize(150,27);
    dtFine->setDate(QDate::currentDate());

    // Aggiunta widget ai rispettivi layout
    vbImporta->addWidget(pbImporta);
    vbImporta->addWidget(pbCrea);

    hbDataInizio->addWidget(lbInizio);
    hbDataInizio->addWidget(dtInizio);

    hbDataFine->addWidget(lbFine);
    hbDataFine->addWidget(dtFine);

    vbOnline->addWidget(leCity);
    vbOnline->addLayout(hbDataInizio);
    vbOnline->addLayout(hbDataFine);
    vbOnline->addWidget(pbOttieni);

    // Layout assegnati ai rispettivi QGroupBox
    gbFile->setLayout(vbImporta);
    gbOnline->setLayout(vbOnline);

    // Widget aggiunti alla griglia principale
    grLayout->addWidget(lbTitolo, 0, 0, 1, -1);
    grLayout->addWidget(gbFile, 1, 0);
    grLayout->addWidget(lbOppure, 1, 1);
    grLayout->addWidget(gbOnline, 1, 2);
    grLayout->addWidget(lbErrore, 2, 0, 1, -1);

    // Inizializzazione finestra e assegnazione layout principale
    finestra = new QWidget();
    finestra->setLayout(grLayout);

    // Formattazione finestra
    setWindowTitle("AirQuality Charts");
    resize(250,150);
    setCentralWidget(finestra);

    // Connect varie
    connect(this,SIGNAL(filePronto(const QJsonDocument*)),this,SLOT(creoModel(const QJsonDocument*)));
    connect(&aqr,SIGNAL(readReady(const QJsonDocument*)),this,SLOT(creoModel(const QJsonDocument*)));
    connect(pbImporta,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(pbOttieni,SIGNAL(clicked()),this,SLOT(getAirQuality()));
    connect(pbCrea,SIGNAL(clicked()),this,SLOT(apriFileVuoto()));
    connect(this, SIGNAL(modelCreato(Dati*)), this, SLOT(apriFinestra(Dati*)));
    connect(this,SIGNAL(mostraErrore(QString)),this,SLOT(updateErrorLabel(QString)));
}

void StartWindow::chooseFile()
{
    lbErrore->setVisible(false);

    QString fileName = QFileDialog::getOpenFileName(this, "Scegli un file grafico","","File JSON (*.json)");
    if(fileName!=NULL){
        if(Dati::isDati(openJson(fileName)))
            emit filePronto(&openJson(fileName));
        else
            emit mostraErrore(fileNonValido);
    }
}

void StartWindow::getAirQuality()
{
    lbErrore->setVisible(false);
    QDate fine = dtFine->date();
    QDate inizio = dtInizio->date();

    try {
        Coordinate coords_citta = coordsResolver(leCity->text());
        QDate primadataDisp = primadataDisp.fromString("2020-11-27", Qt::ISODate);

        if(inizio>=primadataDisp && fine<=QDate::currentDate() && fine>inizio)
            aqr.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
        else
            throw std::invalid_argument("Date non valide");
    } catch(std::domain_error& a) {
        emit mostraErrore(cittaNonPresente);
    } catch(std::invalid_argument& b) {
        emit mostraErrore(dateNonCorrette);
    }
}

Coordinate StartWindow::coordsResolver(const QString& citta) const
{
    QJsonObject json_obj;
    QJsonArray json_array = getCitiesJson().array();

    for(int i=0; i<json_array.count(); ++i) {
        json_obj = json_array.at(i).toObject();
        if(json_obj["city_ascii"]==citta){
            return Coordinate(json_obj.value("lat").toDouble(), json_obj.value("lng").toDouble());
        }
    }
    throw std::domain_error("La città inserita non è disponibile");
}

QJsonDocument& StartWindow::getCitiesJson() const
{
    QJsonDocument* json = new QJsonDocument(openJson(":/worldcities.json"));

    if(!json->isArray())
        throw std::invalid_argument("Il file che si sta cercando di aprire non contiene un JSON");

    return *json;
}

QCompleter* StartWindow::createCompleter() const
{
    QStringList listaCitta;
    QJsonArray json_array = getCitiesJson().array();

    for(int i=0; i<json_array.count(); ++i)
        listaCitta.append(json_array.at(i).toObject().value("city_ascii").toString());

    QCompleter* citylist = new QCompleter(listaCitta);
    citylist->setCaseSensitivity(Qt::CaseInsensitive);
    return citylist;
}

void StartWindow::creoModel(const QJsonDocument* datiDoc, const QDateTime& dataInizio, const Coordinate& c)
{
    Dati* dati = new Dati(datiDoc->object(), dataInizio, c);
    emit modelCreato(dati);
}

QJsonDocument& StartWindow::openJson(const QString& path) const
{
    QString val;
    QFile file;

    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument* json = new QJsonDocument(QJsonDocument::fromJson(val.toLocal8Bit()));
    if(json->isNull())
        throw std::invalid_argument("Il file che si sta cercando di aprire non é valido");
    return *json;
}

void StartWindow::ottieniDati(const QString& citta, const QDate& inizio, const QDate& fine) const
{
    Coordinate coords_citta = coordsResolver(citta);
    QDate inizioAPI = inizioAPI.fromString("2020-11-27", Qt::ISODate);

    if(inizio>=inizioAPI && fine<=QDate::currentDate() && fine>inizio)
        aqr.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
    else
        throw std::invalid_argument("Date non valide");
}

void StartWindow::saveJSonReply(const QJsonDocument* doc) const
{
    if(doc->isObject()) {
        QString filename= QString(QDateTime::currentDateTimeUtc().toString(Qt::ISODate)).append(".json");
        QFile fileRichiesta(filename);

        fileRichiesta.open(QIODevice::ReadWrite);
        fileRichiesta.write(doc->toJson());
        fileRichiesta.close();
    }
}

void StartWindow::apriFinestra(Dati* d)
{
    finestra = new ChartsViewer(d, this);
    finestra->show();
}

void StartWindow::updateErrorLabel(const QString& param)
{
    lbErrore->setVisible(true);
    lbErrore->setText(param);
}

void StartWindow::apriFileVuoto()
{
    QJsonDocument *doc = &openJson(":/fileVuoto.json");
    bool confirm = false;
    QPair<QDateTime,QString> data = DateDialog::getDateTime(this, &confirm);
    if(confirm)
        creoModel(doc, data.first, coordsResolver(data.second));
}
