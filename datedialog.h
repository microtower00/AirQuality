#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include "cittaedit.h"

#include "coordinate.h"

class DateDialog : public QDialog
{
public:
    explicit DateDialog(QWidget *parent = nullptr);
    static QPair<QDateTime,QString> getDateTime(QWidget *parent, bool *ok = nullptr);

private:
    QLabel* labelData;
    QLabel* labelLatLon;

    QDateTimeEdit* insertDate;
    CittaEdit* latLon;
};

#endif // DATEDIALOG_H
