#ifndef MODEL_H
#define MODEL_H

#include <AirQualityRetriever.h>
#include <QFile>
#include <QFileDialog>
#include <QGeoCoordinate>

class Model: public QObject
{
    Q_OBJECT
public:
    Model(QString);
    //Non ancora implementato
    QGeoCoordinate coordsResolver(QString) const;
    QStringList getCompleterList() const;
public slots:
    void ottieniDati(QString, QDate, QDate) const;
    void saveJSonReply(const QJsonDocument*) const;
    void openFileDialog(QWidget*) const;

signals:
    void savedFile(QString) const;
private:
    AirQualityRetriever aqRet;
};

#endif // MODEL_H
