#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLineEdit>

#include "coordinate.h"

class DateDialog : public QDialog
{
public:
    explicit DateDialog(QWidget *parent = nullptr);
    static QPair<QDateTime,Coordinate> getDateTime(QWidget *parent, bool *ok = nullptr);

private:
    QLabel* labelData;
    QLabel* labelLat;
    QLabel* labelLon;

    QDateTimeEdit* insertDate;
    QLineEdit* lat;
    QLineEdit* lon;
};

#endif // DATEDIALOG_H
