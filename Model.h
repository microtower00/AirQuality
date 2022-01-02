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
    QGeoCoordinate coordsResolver(const QString)const;
    QList<QString> getCompleterList()const;
public slots:
    void ottieniDati(QString,QDate,QDate);
    void saveJSonReply(QJsonDocument*);
    void openFileDialog(QWidget*);

signals:
    void savedFile(QString);
private:
    AirQualityRetriever aqRet;
};

#endif // MODEL_H
