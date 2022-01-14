#include "selectorview.h"

#include <iostream>
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    SelectorView s;
    s.show();//Model model("7b6bde71c02400af4d2b61da7b315b31");

    return a.exec();
}
