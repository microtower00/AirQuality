#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "airqualityretriever.h"
#include "Model/dati.h"
#include "View/dataviewer.h"

#include <QMainWindow>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <iostream>
#include <QDebug>
#include <QFileDialog>
#include <QGeoCoordinate>
#include <QCompleter>

/*!
 * @brief   La classe FPickerController si occupa della interazione inizale con l'utente all'interno dell'app AirQuality
 *          La classe possiede é una mainwindow e possiede diversi widget attraverso i quali l'utente puó specificare da
 *          quale file creare il model
 */
class StartWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*!
     * @brief FPickerController É il metodo costruttore della classe che inizializza l'interfaccia grafica dell'applicazione
     * @param parent            Widget parent della mainwindow
     */
    explicit StartWindow(QWidget *parent = nullptr);

    /*!
     * @brief coordsResolver    Ritorna le coordinate della cittá passata come parametro
     * @param citta             Cittá della quale ottenere le coordinate, deve essere presente nel file worldcities.json
     * @return                  Oggetto QGeoCoordinate con le coordinate richieste
     */
    QGeoCoordinate coordsResolver(QString citta) const;

    /*!
     * @brief validCity Verifica se la cittá inserita é presente nell'elenco worldcities.json
     * @param citta     Stringa con il nome della cittá
     * @return
     */
    bool validCity(QString citta) const;

    /*!
     * @brief getCitiesJson Apre il file contenente l'elenco di cittá.
     * @return              Ritorna il QJSonObject del file worldcities.json
     */
    QJsonDocument& getCitiesJson() const;

    /*!
     * @brief createCompleter   Scorre tutto il file worldcities.json per creare una lista per il completer
     * @return                  Completer inizializzato con tutte le cittá
     */
    QCompleter* createCompleter() const;

    /*!
     * @brief openJSon      Metodo che ritorna un JsonDocument aperto da un file
     * @param relativePath  Path del file da aprire
     * @return              Riferimento al JSonDocument
     */
    QJsonDocument& openJson(QString relativePath) const;

public slots:
    void chooseFile();
    void getAirQuality();
    void creoModel(const QJsonDocument*);
    void ottieniDati(QString, QDate, QDate) const;
    void saveJSonReply(const QJsonDocument* doc) const;

signals:
    void filePronto(const QJsonDocument*);
    void modelCreato(Dati);

private:
    const static QString APIKEY;

    AirQualityRetriever aqr;
    DataViewer* data;

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

    QStringList wordList;
    QCompleter *completer;

    QWidget *finestra;

    QPushButton *bottoneCambio;

    QLabel *erroreCityLab;
    QLabel *erroreDateLab;

    AirQualityRetriever aqRet;
};

#endif // STARTWINDOW_H
