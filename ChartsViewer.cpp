#include "ChartsViewer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include "AirQualityRetriever.h"
#include<iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QLabel *titolo = new QLabel("AirQuality Charts",this);
    QLabel *oppure = new QLabel("oppure",this);

    QVBoxLayout *colonnaBott = new QVBoxLayout();
    QPushButton *bottone1 = new QPushButton("Apri file");
    QFileDialog *file = new QFileDialog(this, "Open file", "C://");
    QPushButton *bottone2 = new QPushButton("Ottieni da OpenWeather");
    QComboBox *combo = new QComboBox();

    connect(bottone1, SIGNAL(clicked()),file,SLOT(open()));

    colonnaBott->addWidget(titolo);
    colonnaBott->addWidget(bottone1);
    colonnaBott->addWidget(oppure);
    colonnaBott->addWidget(bottone2);
    colonnaBott->addWidget(combo);

    resize(500,500);

    QWidget *finestra = new QWidget();
    finestra->setLayout(colonnaBott);

    setCentralWidget(finestra);
}

MainWindow::~MainWindow()
{
}
