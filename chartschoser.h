#ifndef CHARTSCHOSER_H
#define CHARTSCHOSER_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>

class ChartsChoser : public QMainWindow
{
    Q_OBJECT
public slots:

public:
    ChartsChoser(QWidget *parent = nullptr);
    ~ChartsChoser();
private:
    QLabel *testLab;
    QWidget *testFin;
    /*
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

    QPushButton *bottoneCambio;
    */
};

#endif // CHARTSCHOSER_H
