#ifndef TABLECHOOSER_H
#define TABLECHOOSER_H

#include "Model/dati.h"
#include "mytableview.h"

#include <QFileDialog>
#include <QGroupBox>
#include <QPushButton>

class TableChooser : public QGroupBox
{
    Q_OBJECT
  private:
    Dati *data;

    QVBoxLayout *mainLayout;

    QPushButton *pbTabella;
    QPushButton *pbSalvaFile;
    QPushButton *pbAddRiga;
    QPushButton *pbRemRiga;

    MyTableView *tabella;

  public:
    TableChooser (Dati *);
    MyTableView *getTabella () const;
    Dati *getDati () const;

  public slots:
    void enableTabella ();
    void disableTabella ();
    void iniziaSalvataggio ();
};

#endif // TABLECHOOSER_H
