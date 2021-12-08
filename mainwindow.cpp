#include "mainwindow.h"
#include <QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QComboBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    QLabel *titolo = new QLabel("AirQuality Charts",this);
    QLabel *oppure = new QLabel("oppure",this);

    QVBoxLayout *colonnaBott = new QVBoxLayout(this);
    QPushButton *bottone1 = new QPushButton("Apri File");
    QPushButton *bottone2 = new QPushButton("Ottieni da OpenWeather");
    QComboBox *combo = new QComboBox();

    colonnaBott->addWidget(titolo);
    colonnaBott->addWidget(bottone1);
    colonnaBott->addWidget(oppure);
    colonnaBott->addWidget(bottone2);
    colonnaBott->addWidget(combo);

    QWidget *finestra = new QWidget();
    finestra->setLayout(colonnaBott);

    setCentralWidget(finestra);
}

MainWindow::~MainWindow()
{
}
