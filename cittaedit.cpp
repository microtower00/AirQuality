#include "cittaedit.h"

CittaEdit::CittaEdit(QString placeholder, QWidget* parent):QLineEdit(parent){
    setPlaceholderText(placeholder);
    setMinimumSize(200,27);
    setCompleter(createCompleter());
}

QCompleter* CittaEdit::createCompleter() const
{
    QStringList listaCitta;
    QJsonArray json_array = getCitiesJson().array();

    for(int i=0; i<json_array.count(); ++i)
        listaCitta.append(json_array.at(i).toObject().value("city_ascii").toString());

    QCompleter* citylist = new QCompleter(listaCitta);
    citylist->setCaseSensitivity(Qt::CaseInsensitive);
    return citylist;
}

QJsonDocument& CittaEdit::getCitiesJson() const
{   QString val;
    QFile file;

    file.setFileName(":/worldcities.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument* json = new QJsonDocument(QJsonDocument::fromJson(val.toLocal8Bit()));
    if(json->isNull())
        throw std::invalid_argument("Il file che si sta cercando di aprire non é valido");

    if(!json->isArray())
        throw std::invalid_argument("Il file che si sta cercando di aprire non contiene un JSON");

    return *json;
}
