#include "Windows/startwindow.h"

#include <iostream>
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    StartWindow s;
    s.show();

    return a.exec();
}
