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

class dataviewer : public QMainWindow
{
    Q_OBJECT
public slots:
    //funzione che crea la tabella e mostra la finestra
    void createTable(QJsonObject);
public:
    //costruttore che non fa assolutamente niente
    dataviewer(QWidget *parent = nullptr);
private:
    QTableWidget* tableJS;
    QWidget* mainW;
    QVBoxLayout* layout;
signals:

};

#endif // DATAVIEWER_H
