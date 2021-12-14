#ifndef CHARTSVIEWER_H
#define CHARTSVIEWER_H

#include <QMainWindow>
#include<QGeoCoordinate>
#include <QJsonDocument>

class ChartsViewer : public QMainWindow
{
    Q_OBJECT
public slots:
    void receiveJson(QJsonDocument*);
public:
    ChartsViewer(QWidget *parent = nullptr);
    ~ChartsViewer();
};
#endif // CHARTSVIEWER_H
