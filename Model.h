#ifndef MODEL_H
#define MODEL_H

#include <AirQualityRetriever.h>
#include <QFile>
#include <QFileDialog>
#include <QGeoCoordinate>
#include <QCoreApplication>
#include <exception>

class Model: public QObject
{
    Q_OBJECT
public:
    Model(QString);
    QGeoCoordinate coordsResolver(QString) const;
    QStringList getCompleterList() const;
    QJsonDocument apriWC() const;
    QJsonDocument openJSon(QString path) const;
public slots:
    void ottieniDati(QString, QDate, QDate) const;
    void saveJSonReply(const QJsonDocument*) const;
    void openFileDialog(QWidget*) const;

signals:
    void savedFile(QString) const;
    void savedObj(QJsonObject) const;
private:
    AirQualityRetriever aqRet;
};

#endif // MODEL_H
