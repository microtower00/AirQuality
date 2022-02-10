#ifndef DATEDIALOG_H
#define DATEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QDateTimeEdit>
#include <QFormLayout>
#include <QDialogButtonBox>

class DateDialog : public QDialog
{
public:
    explicit DateDialog(QWidget *parent = nullptr);
    static QDateTime getDateTime(QWidget *parent, bool *ok = nullptr);

private:
    QLabel* label;
    QDateTimeEdit* insertDate;
};

#endif // DATEDIALOG_H
