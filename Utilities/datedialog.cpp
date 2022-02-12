#include "datedialog.h"

DateDialog::DateDialog (QWidget *parent) : QDialog (parent)
{
    QFormLayout *lytMain = new QFormLayout (this);

    labelData = new QLabel ("Inserisci la data di inizio", this);
    insertDate = new QDateEdit (QDate::currentDate (), this);
    lytMain->addRow (labelData, insertDate);

    labelLatLon
        = new QLabel ("Inserisci la città di registrazione dei dati", this);
    latLon = new CittaEdit ("", this);
    lytMain->addRow (labelLatLon, latLon);

    QDialogButtonBox *buttonBox = new QDialogButtonBox (
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    lytMain->addWidget (buttonBox);

    bool conn = connect (buttonBox, &QDialogButtonBox::accepted, this,
                         &DateDialog::accept);
    Q_ASSERT (conn);

    conn = connect (buttonBox, &QDialogButtonBox::rejected, this,
                    &DateDialog::reject);
    Q_ASSERT (conn);
    this->resize (400, 100);
    setLayout (lytMain);
}

QPair<QDateTime, QString>
DateDialog::getDateTime (QWidget *parent, bool *ok)
{
    DateDialog *dialog = new DateDialog (parent);

    const int ret = dialog->exec ();
    if (ok)
        *ok = !!ret;

    dialog->deleteLater ();

    return QPair<QDateTime, QString> (dialog->insertDate->dateTime (),
                                      dialog->latLon->text ());
}
