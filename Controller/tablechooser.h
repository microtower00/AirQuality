#ifndef TABLECHOOSER_H
#define TABLECHOOSER_H

#include "Model/dati.h"
#include "View/mytableview.h"

#include <QGroupBox>
#include <QPushButton>
#include <QFileDialog>

class TableChooser : public QGroupBox
{
    Q_OBJECT
private:
    Dati data;

    QVBoxLayout* mainLayout;

    QPushButton* pbTabella;
    QPushButton* pbSalvaFile;
    QPushButton* pbAddRiga;
    QPushButton* pbRemRiga;

    MyTableView* tabella;

public:
    TableChooser(const Dati&);
    MyTableView* getTabella() const;

public slots:
    //void createTable();
    void iniziaSalvataggio();
};

#endif // TABLECHOOSER_H
