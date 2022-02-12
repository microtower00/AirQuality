#ifndef MYTABLEVIEW_H
#define MYTABLEVIEW_H

#include "Model/dati.h"
#include <QDateTime>
#include <QHeaderView>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QTableView>
#include <QTableWidget>
#include <QVBoxLayout>

class MyTableView : public QTableView
{
    Q_OBJECT
  public slots:

  public:
    MyTableView (Dati *);

  private:
  signals:
    void tablePronta ();
    void richiestaAggiunta ();
    void richiestaRimossa ();
};

#endif // MYTABLEVIEW_H
