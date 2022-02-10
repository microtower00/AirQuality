#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "airqualityretriever.h"
#include "Model/dati.h"
#include "chartsviewer.h"
#include "datedialog.h"

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
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
private:
    const static QString APIKEY;
    static QString fileNonValido;
    static QString cittaNonPresente;
    static QString dateNonCorrette;

    AirQualityRetriever aqr;
    MyTableView *data;
    ChartsChooser *selettore;

    QGridLayout *grLayout;
    QVBoxLayout *vbImporta;
    QVBoxLayout *vbOnline;
    QHBoxLayout *hbDataInizio;
    QHBoxLayout *hbDataFine;

    QGroupBox *gbFile;
    QGroupBox *gbOnline;

    QLabel *lbTitolo;
    QLabel *lbOppure;
    QLabel *lbInizio;
    QLabel *lbFine;
    QLabel *lbDescr;
    QLabel *lbErrore;

    QLineEdit *leCity;
    QDateEdit *dtInizio;
    QDateEdit *dtFine;

    QPushButton *pbImporta;
    QPushButton *pbOttieni;
    QPushButton *pbCrea;

    QStringList wordList;
    QCompleter *completer;

    QWidget *finestra;

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
    QGeoCoordinate coordsResolver(const QString& citta) const;

    /*!
     * @brief validCity Verifica se la cittá inserita è presente nell'elenco worldcities.json
     * @param citta     Stringa con il nome della cittá
     * @return
     */
    bool validCity(const QString& citta) const;

    /*!
     * @brief getCitiesJson Apre il file contenente l'elenco di città.
     * @return              Ritorna il QJSonObject del file worldcities.json
     */
    QJsonDocument& getCitiesJson() const;

    /*!
     * @brief createCompleter   Scorre tutto il file worldcities.json per creare una lista per il completer
     * @return                  Completer inizializzato con tutte le città
     */
    QCompleter* createCompleter() const;

    /*!
     * @brief openJSon      Metodo che ritorna un JsonDocument aperto da un file
     * @param relativePath  Path del file da aprire
     * @return              Riferimento al JSonDocument
     */
    QJsonDocument& openJson(const QString& relativePath) const;

public slots:
    void chooseFile();
    void getAirQuality();
    void creoModel(const QJsonDocument*, const QDateTime& = QDateTime());
    void ottieniDati(const QString&, const QDate&, const QDate&) const;
    void saveJSonReply(const QJsonDocument* doc) const;
    void apriFileVuoto();
    void apriFinestra(const Dati&);
    void updateErrorLabel(const QString&);

signals:
    void filePronto(const QJsonDocument*);
    void mostraErrore(const QString&);
    void modelCreato(const Dati&);
};

#endif // STARTWINDOW_H
