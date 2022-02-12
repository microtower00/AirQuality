#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "Model/dati.h"
#include "Utilities/airqualityretriever.h"
#include "Utilities/cittaedit.h"
#include "Utilities/coordinate.h"
#include "Utilities/datedialog.h"
#include "Windows/dataviewer.h"

#include <QCompleter>
#include <QDateEdit>
#include <QErrorMessage>
#include <QFileDialog>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

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
    QLabel *lbInfoDati;

    CittaEdit *leCity;
    QDateEdit *dtInizio;
    QDateEdit *dtFine;

    QPushButton *pbImporta;
    QPushButton *pbOttieni;
    QPushButton *pbCrea;

    QStringList wordList;
    QCompleter *completer;

    QErrorMessage *error;

    QWidget *finestra;

  public:
    explicit StartWindow (QWidget *parent = nullptr);
    Coordinate coordsResolver (const QString &citta) const;
    bool validCity (const QString &citta) const;
    QJsonDocument &getCitiesJson () const;
    QCompleter *createCompleter () const;
    QJsonDocument &openJson (const QString &relativePath) const;

  public slots:
    void chooseFile ();
    void getAirQuality ();
    void creoModel (const QJsonDocument *, const QDateTime & = QDateTime (),
                    const Coordinate & = Coordinate (0, 0));
    void ottieniDati (const QString &, const QDate &, const QDate &) const;
    void saveJSonReply (const QJsonDocument *doc) const;
    void apriFileVuoto ();
    void apriFinestra (Dati *);
    void errorDialog (const QString &);

  signals:
    void filePronto (const QJsonDocument *);
    void mostraErrore (const QString &);
    void modelCreato (Dati *);
};

#endif // STARTWINDOW_H
