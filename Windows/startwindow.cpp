#include "startwindow.h"

const QString StartWindow::APIKEY = "7b6bde71c02400af4d2b61da7b315b31";
QString StartWindow::fileNonValido = "Il file che stai cercando di aprire non è supportato.";
QString StartWindow::cittaNonPresente = "La città inserita è vuota o non riconosciuta.";
QString StartWindow::dateNonCorrette = "Le date inserite non sono valide.";

StartWindow::StartWindow(QWidget *parent) : QMainWindow{parent}
{
    grLayout = new QGridLayout();
    vbImporta = new QVBoxLayout();
    vbOnline = new QVBoxLayout();
    hbDataInizio = new QHBoxLayout();
    hbDataFine = new QHBoxLayout();

    gbFile = new QGroupBox("File");
    gbOnline = new QGroupBox("Scarica da internet");

    lbTitolo = new QLabel("AirQuality Charts");
    lbOppure = new QLabel("oppure");
    lbInizio = new QLabel("Inizio");
    lbFine = new QLabel("Fine");
    lbDescr = new QLabel("AirQuality Charts è un programma che consente di creare, importare, scaricare e modificare dati relativi a composizione e qualità dell'aria di determinate città in determinati intervalli di tempo.");
    lbInfoDati = new QLabel("");

    lbDescr->setWordWrap(true);
    lbDescr->setAlignment(Qt::AlignJustify);

    leCity = new CittaEdit("Inserisci città");
    dtInizio = new QDateEdit();
    dtFine = new QDateEdit;

    pbImporta = new QPushButton("Importa");
    pbOttieni = new QPushButton("Ottieni");
    pbCrea = new QPushButton("Crea nuovo");

    error = new QErrorMessage();

    QFont ubuntuF("Ubuntu Thin", 24);
    lbTitolo->setFont(ubuntuF);

    dtInizio->setMinimumSize(150,27);
    dtInizio->setDate(QDate(2020,11,27));
    dtFine->setMinimumSize(150,27);
    dtFine->setDate(QDate::currentDate());

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

    gbFile->setLayout(vbImporta);
    gbOnline->setLayout(vbOnline);

    grLayout->addWidget(lbTitolo, 0, 0, 1, -1);
    grLayout->addWidget(gbFile, 1, 0);
    grLayout->addWidget(lbOppure, 1, 1);
    grLayout->addWidget(gbOnline, 1, 2);
    grLayout->addWidget(lbInfoDati, 3, 0, 1, 3);
    grLayout->addWidget(lbDescr, 4, 0, 1, 3);

    finestra = new QWidget();
    finestra->setLayout(grLayout);

    setWindowTitle("AirQuality Charts");
    resize(425,350);
    setMaximumSize(425,350);
    setMinimumSize(425,350);
    setCentralWidget(finestra);

    connect(this,SIGNAL(filePronto(const QJsonDocument*)),this,SLOT(creoModel(const QJsonDocument*)));
    connect(&aqr,SIGNAL(readReady(const QJsonDocument*)),this,SLOT(creoModel(const QJsonDocument*)));
    connect(pbImporta,SIGNAL(clicked()),this,SLOT(chooseFile()));
    connect(pbOttieni,SIGNAL(clicked()),this,SLOT(getAirQuality()));
    connect(pbCrea,SIGNAL(clicked()),this,SLOT(apriFileVuoto()));
    connect(this, SIGNAL(modelCreato(Dati*)), this, SLOT(apriFinestra(Dati*)));
    connect(this,SIGNAL(mostraErrore(QString)),this,SLOT(errorDialog(QString)));
    connect(&aqr, SIGNAL(erroreRichiesta(QString)), this, SLOT(errorDialog(QString)));
}

void StartWindow::chooseFile()
{
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
    QDate fine = dtFine->date();
    QDate inizio = dtInizio->date();

    try {
        Coordinate coords_citta = coordsResolver(leCity->text());
        QDate primadataDisp = primadataDisp.fromString("2020-11-27", Qt::ISODate);

        if(inizio>=primadataDisp && fine<=QDate::currentDate() && fine>inizio) {
            lbInfoDati->setText("Ottengo i dati...");
            aqr.retrieveHistorical(coords_citta.latitude(), coords_citta.longitude(), inizio, fine);
        } else
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
    lbInfoDati->setText("");
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
    finestra = new DataViewer(d, this);
    finestra->show();
}

void StartWindow::errorDialog(const QString& param)
{
    error->showMessage(param);
}

void StartWindow::apriFileVuoto()
{
    QJsonDocument *doc = &openJson(":/fileVuoto.json");
    bool confirm = false;
    QPair<QDateTime,QString> data = DateDialog::getDateTime(this, &confirm);
    try {
        if(confirm)
            creoModel(doc, data.first, coordsResolver(data.second));
    }  catch (std::domain_error e) {
        errorDialog(e.what());
    }
}
