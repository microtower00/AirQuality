#ifndef CHARTSVIEWER_H
#define CHARTSVIEWER_H

#include <QMainWindow>
#include<QGeoCoordinate>
#include <QJsonDocument>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QComboBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QJsonObject>
#include <iostream>
#include <QCompleter>

#include "chartschoser.h"
#include "Controller/airqualityretriever.h"

class ChartsViewer : public QMainWindow
{
    Q_OBJECT
public slots:
    void bottoneOttieni();
    void cliccatoImporta();
public:
    ChartsViewer(QWidget *parent = nullptr);
    void setCompleterList(QStringList);
    ~ChartsViewer();
private:
    ChartsChoser* charts;

    QLabel *jsLabel;
    QLabel *titolo;
    QLabel *oppure;
    QLabel *inizio;
    QLabel *fine;

    QVBoxLayout *mainCol;

    QHBoxLayout *rigaTitle;
    QHBoxLayout *rigaAzioni;

    QVBoxLayout *importaVbox;
    QVBoxLayout *openWeatherVbox;
    QGroupBox *importa;
    QGroupBox *openWeather;

    QHBoxLayout *rigaDataInizio;
    QHBoxLayout *rigaDataFine;

    QPushButton *apriFileButton;
    QPushButton *openWeatherButton;
    QLineEdit *cityText;
    QDateEdit *dataInizio;
    QDateEdit *dataFine;

    QFileDialog *file;


    QStringList wordList;
    QCompleter *completer;

    QWidget *finestra;

    QPushButton *bottoneCambio;

    QLabel *erroreCityLab;
    QLabel *erroreDateLab;


signals:
    void cliccatoOttieni();
    void needDati(QString, QDate, QDate);
};


#endif // CHARTSVIEWER_H
