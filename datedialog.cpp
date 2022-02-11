#include "datedialog.h"

DateDialog::DateDialog(QWidget *parent) : QDialog(parent){
    QFormLayout *lytMain = new QFormLayout(this);

    labelData = new QLabel("Inserisci la data di inizio",this);
    insertDate = new QDateEdit(QDate::currentDate(), this);
    lytMain->addRow(labelData,insertDate);

    labelLat = new QLabel("Inserisci la latitudine alla quale sono stati registrati i dati",this);
    lat = new QLineEdit();
    lat->setValidator( new QDoubleValidator(0, 100, 2, this) );
    lytMain->addRow(labelLat,lat);
    qDebug("crasho");

    labelLon = new QLabel("Inserisci la longitudine");
    lon = new QLineEdit();
    lon->setValidator( new QDoubleValidator(0, 100, 2, this) );
    lytMain->addRow(labelLon,lon);
    qDebug("crasho");

    QDialogButtonBox *buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &DateDialog::accept);
    Q_ASSERT(conn);

    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &DateDialog::reject);
    Q_ASSERT(conn);
    this->resize(400,100);
    setLayout(lytMain);
}

QPair<QDateTime,Coordinate> DateDialog::getDateTime(QWidget *parent, bool *ok){
    DateDialog *dialog = new DateDialog(parent);

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    dialog->deleteLater();

    return QPair<QDateTime,Coordinate>(dialog->insertDate->dateTime(),Coordinate(dialog->lat->text().toDouble(),dialog->lon->text().toDouble()));
}
