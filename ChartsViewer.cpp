#include "ChartsViewer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QGroupBox>
#include <QTextEdit>
#include <QDateEdit>

#include "AirQualityRetriever.h"
#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
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
    QTextEdit *cityText = new QTextEdit();
    QDateEdit *dataInizio = new QDateEdit();
    QDateEdit *dataFine = new QDateEdit;

    QFileDialog *file = new QFileDialog(this, "Open file", "C://");

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

    resize(250,150);

    QWidget *finestra = new QWidget();
    finestra->setLayout(mainCol);

    setCentralWidget(finestra);
}

MainWindow::~MainWindow()
{
}
