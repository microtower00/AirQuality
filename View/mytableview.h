#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

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
#include<QHeaderView>
#include "Model/dati.h"

class MyTableView : public QTableView
{
    Q_OBJECT
public slots:

public:
    MyTableView(Dati&);
private:

signals:
    void tablePronta();
    void richiestaAggiunta();

};

#endif // MYTABLEVIEW_H
