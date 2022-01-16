#ifndef CHARTSCHOSER_H
#define CHARTSCHOSER_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class ChartsChoser : public QMainWindow
{
    Q_OBJECT
public slots:

public:
    ChartsChoser(QWidget *parent = nullptr);
    ~ChartsChoser();
private:
    QLabel *testLab;
    QPushButton* bottLinee;
    QPushButton* bottArea;
    QPushButton* bottIsto;
    QPushButton* bottPlot;
    QPushButton* bottRadar;

    QWidget *testFin;
};

#endif // CHARTSCHOSER_H
