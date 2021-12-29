#include "chartsviewer.h"
#include "AirQualityRetriever.h"
#include "chartschoser.h"

#include <iostream>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChartsViewer w;
    w.show();

    return a.exec();
}
