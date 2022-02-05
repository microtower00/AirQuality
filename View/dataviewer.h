#ifndef DATAVIEWER_H
#define DATAVIEWER_H

#include <QMainWindow>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTableView>
#include <QTableWidget>
#include <QDebug>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QDateTime>
#include <QLabel>
#include "Model/dati.h"

class DataViewer : public QTableWidget
{
    Q_OBJECT
public slots:

public:
    DataViewer(Dati);
private:

signals:
    void tablePronta();

};

#endif // DATAVIEWER_H
