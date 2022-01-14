#ifndef SELECTORVIEW_H
#define SELECTORVIEW_H

#include<iostream>
#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>

class SelectorView : public QMainWindow
{
    Q_OBJECT
public:
    explicit SelectorView(QWidget *parent = nullptr);

signals:
private:
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
};

#endif // SELECTORVIEW_H
