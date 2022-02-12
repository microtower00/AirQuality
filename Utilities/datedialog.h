#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include "cittaedit.h"
#include <QDateTimeEdit>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>

#include "coordinate.h"

class DateDialog : public QDialog
{
  public:
    explicit DateDialog (QWidget *parent = nullptr);
    static QPair<QDateTime, QString> getDateTime (QWidget *parent,
                                                  bool *ok = nullptr);

  private:
    QLabel *labelData;
    QLabel *labelLatLon;

    QDateTimeEdit *insertDate;
    CittaEdit *latLon;
};

#endif // DATEDIALOG_H
