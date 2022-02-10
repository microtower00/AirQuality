#include "datedialog.h"

DateDialog::DateDialog(QWidget *parent) : QDialog(parent){
    QFormLayout *lytMain = new QFormLayout(this);

    label = new QLabel("Inserisci la data di inizio",this);
    insertDate = new QDateEdit(QDate::currentDate(), this);
    lytMain->addRow(label,insertDate);

    QDialogButtonBox *buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &DateDialog::accept);
    Q_ASSERT(conn);

    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &DateDialog::reject);
    Q_ASSERT(conn);
    this->resize(400,100);
    setLayout(lytMain);
}

QDateTime DateDialog::getDateTime(QWidget *parent, bool *ok){
    DateDialog *dialog = new DateDialog(parent);

    QStringList list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    dialog->deleteLater();

    return dialog->insertDate->dateTime();
}
