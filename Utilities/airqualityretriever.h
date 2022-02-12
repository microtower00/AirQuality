#ifndef AIRQUALITYRETRIEVER_H
#define AIRQUALITYRETRIEVER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class AirQualityRetriever : public QObject
{
    Q_OBJECT

  private:
    QNetworkAccessManager *manager;
    QString apikey;

  public:
    AirQualityRetriever (QString = "7b6bde71c02400af4d2b61da7b315b31");
    void retrieveHistorical (const double &, const double &, const QDate &,
                             const QDate &) const;

  public slots:
    QJsonDocument replyEnded (QNetworkReply *);

  signals:
    void readReady (const QJsonDocument *);
    void erroreRichiesta (const QString &);
};

#endif // AIRQUALITYRETRIEVER_H
