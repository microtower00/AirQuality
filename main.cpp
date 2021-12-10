#include "ChartsViewer.h"
#include "AirQualityRetriever.h"

#include <iostream>
#include <QApplication>
#include <QJsonObject>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*AirQualityRetriever *aq = new AirQualityRetriever("a");
    QJsonDocument risp = aq->retrieve(5,5);
    qDebug() << risp.isObject();
    if( risp.isObject() )
            {
                QJsonObject jsonObj = risp.object();
                if( jsonObj.contains("coord") ){
                    qDebug()<<"Dioextragas";
                }else{
                    qDebug()<<"DioextraLaidr";
                }
    }*/
    return a.exec();
}
