#include "mychartview.h"

using namespace QtCharts;

const int MAXCO = 40000;
const int MAXSO2 = 150;
const int MAXNO = 30;
const int MAXNO2 = 200;
const int MAXO3 = 65;
const int MAXNH3 = 18;
const int MAXPM10 = 50;
const int MAXPM2_5 = 25;

QMap<QString,double> MASSIMICONSENTITI;

MyChartView::MyChartView(const Dati& d) : data(d)
{
    MASSIMICONSENTITI.insert("co",MAXCO);
    MASSIMICONSENTITI.insert("so2",MAXSO2);
    MASSIMICONSENTITI.insert("nh3",MAXNH3);
    MASSIMICONSENTITI.insert("no",MAXNO);
    MASSIMICONSENTITI.insert("no2",MAXNO2);
    MASSIMICONSENTITI.insert("o3",MAXO3);
    MASSIMICONSENTITI.insert("pm10",MAXPM10);
    MASSIMICONSENTITI.insert("pm2_5",MAXPM2_5);

    this->setRenderHint(QPainter::Antialiasing);
}

void MyChartView::setCompScelti(const QStringList& compScelti) {
    comp = compScelti;
    resize(1250,750);
}

QMap<QString, QtCharts::QLineSeries*> MyChartView::genericLAchart() {
    resetView();
    resize(1250,750);
    emit chartPronto();
    //MyChartView::show();

    QList<QMap<QString, double>> dati = data.getDati();
    QMap<QString, QtCharts::QLineSeries*> series;

    // creo le serie che poi andranno inserite nella mappa di serie
    QtCharts::QLineSeries* serie;
    for(auto componente:comp){
        serie = new QtCharts::QLineSeries();
        for(auto itDati:dati) {
            serie->append(QPointF(data.getDateFromDouble(itDati.value("Data")).toMSecsSinceEpoch(),itDati.value(componente)));
        }
        // inserimento nella mappa
        series.insert(componente, serie);
    }

    // asse X
    asseX = new QtCharts::QDateTimeAxis;
    asseX->setFormat("dd-MM-yyyy h:mm");
    asseX->setTickCount(12);
    this->chart()->addAxis(asseX, Qt::AlignBottom);

    // asse Y
    asseY = new QtCharts::QValueAxis();
    this->chart()->addAxis(asseY, Qt::AlignLeft);

    return series;
}

void MyChartView::lineChart(){

    QMap<QString, QtCharts::QLineSeries*> series = genericLAchart();

    // per ogni serie nella mappa assegno il nome del componente e i relativi assi
    for(auto it=series.begin(); it!=series.end(); ++it){
        this->chart()->addSeries(*it);
        it.value()->setName(it.key());
        it.value()->attachAxis(asseX);
        it.value()->attachAxis(asseY);
    }

    //setto il massimo di Y al massimo valore tra tutte le serie
    asseY->setMin(0);
    asseY->setMax(comp.first()!="aqi" ? maxValueFromListSeries(series.values()) : maxValueFromListSeries(series.values())+10);
    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::areaChart(){

    QMap<QString, QtCharts::QLineSeries*> series = genericLAchart();

    // shifto tutte le linseries del massimo della precedente per evitare overlapping
    for(auto it=series.begin()+1; it!=series.end(); ++it)
        *it=sommaY(*it, *(it-1));

    // per ogni serie nella mappa assegno il nome del componente e i relativi assi
    // bonus: creo una QAreaSeries tra la lineseries corrente e la precedente
    QAreaSeries *aSeries;
    for(auto it=series.begin(); it!=series.end(); ++it){
        aSeries = new QAreaSeries(*it, it!=series.begin() ? *(it-1) : Q_NULLPTR);
        this->chart()->addSeries(aSeries);
        aSeries->setName(it.key());
        aSeries->attachAxis(asseX);
        aSeries->attachAxis(asseY);
    }

    //setto il massimo di Y al massimo valore tra tutte le serie
    asseY->setMin(0);
    asseY->setMax(maxValueFromListSeries(series.values()));
    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::barChart(){
    resetView();
    emit chartPronto();
    //MyChartView::show();

    // tutto ciò che è stato fatto qua sotto è spiegato abbastanza bene nella doc di QBarSeries (barChartExample) (sicuramente spiegato meglio di quanto potrei fare io che sono cotto)
    QList<QtCharts::QBarSet*> componenti;
    for(auto it:comp)
        componenti.push_back(new QtCharts::QBarSet(it));

    QList<QMap<QString, double>> dati = data.getDati();

    QtCharts::QBarSeries *serie = new QtCharts::QBarSeries();

    for(auto it=comp.begin(); it!=comp.end(); ++it) {
        for(auto itDati:dati) {
            *componenti[(std::distance(comp.begin(), it))]<< itDati.value(*it);
            serie->append(componenti[(std::distance(comp.begin(), it))]);
        }
    }

    this->chart()->addSeries(serie);
    QtCharts::QBarCategoryAxis* asse = new QtCharts::QBarCategoryAxis();

    for(auto itDati:dati) {
        asse->append(data.getDateFromDouble(itDati.value("Data")).toString(Qt::ISODate));
    }
    asse->setRange(QDateTime::currentDateTime().addMonths(-1).toString(),QDateTime::currentDateTime().toString());
    this->chart()->createDefaultAxes();
    this->chart()->setAxisX(asse, serie);

    this->chart()->legend()->setVisible(true);
    this->chart()->legend()->setAlignment(Qt::AlignBottom);
}

void MyChartView::radarChart(){
    resetView();
    emit chartPronto();
    //MyChartView::show();

    QList<QMap<QString, double>> dati = data.getDati();
    QMap<QString,double> mediePrimoGiorno;
    QMap<QString,double> medieUltimoGiorno;

    //prendo la media di tutti i componenti nel primo giorno e nell'ultimo
    QString giornoInizio = QDateTime::fromTime_t(dati.at(0).value("Data")).toString("dd-MM-yyyy");
    QString giornoFine = QDateTime::fromTime_t(dati.at(dati.length()-1).value("Data")).toString("dd-MM-yyyy");

    for(auto record:dati){
        //se é del giorno di inizio, itera e fai media
        if(QDateTime::fromTime_t(record.value("Data")).toString("dd-MM-yyyy")==giornoInizio){
            for(auto componente: comp)
                mediePrimoGiorno.insert(componente, (mediePrimoGiorno.value(componente)+record.value(componente))/2);
        }
        //se é l'ultimo giorno, itera e fai la media
        else if(QDateTime::fromTime_t(record.value("Data")).toString("dd-MM-yyyy")==giornoFine) {
            for(auto componente: comp)
                medieUltimoGiorno.insert(componente, (medieUltimoGiorno.value(componente)+record.value(componente))/2);
        }
    }

    QLineSeries *seriesFirstDay = new QLineSeries();
    seriesFirstDay->setName("Giorno iniziale");

    QLineSeries *seriesLastDay = new QLineSeries();
    seriesLastDay->setName("Giorno finale");

    QLineSeries *valRiferimento = new QLineSeries();
    valRiferimento->setName("Valori massimi consentiti");

    mediePrimoGiorno.remove("Data");
    mediePrimoGiorno.remove("aqi");

    medieUltimoGiorno.remove("Data");
    medieUltimoGiorno.remove("aqi");

    int tickN=0;

    //creo una mappa per i fondo scala di ogni componente
    QMap<QString, double> fondoScala;
    for(auto componente:comp)
        fondoScala.insert(componente, mediePrimoGiorno.value(componente) > MASSIMICONSENTITI.value(componente) ? std::max(mediePrimoGiorno.value(componente),medieUltimoGiorno.value(componente)) : std::max(MASSIMICONSENTITI.value(componente),medieUltimoGiorno.value(componente)));

    //inserisco i punti
    for(auto componente:comp){
        seriesFirstDay->append(QPointF(360/mediePrimoGiorno.values().length()*tickN, mediePrimoGiorno.value(componente)*100/fondoScala.value(componente)));
        valRiferimento->append(QPointF(360/comp.size()*tickN, MASSIMICONSENTITI.value(componente)*100/fondoScala.value(componente)));
        seriesLastDay->append(QPointF(360/medieUltimoGiorno.values().length()*tickN, medieUltimoGiorno.value(componente)*100/fondoScala.value(componente)));
        ++tickN;
    }

    //Chiudo il "cerchio"
    double fondoInizio = fondoScala.values().at(0);
    seriesFirstDay->append(QPointF(360, mediePrimoGiorno.values().at(0)*100/fondoInizio));
    seriesLastDay->append(QPointF(360, medieUltimoGiorno.values().at(0)*100/fondoInizio));
    valRiferimento->append(QPointF(360, MASSIMICONSENTITI.value(comp.first())*100/fondoInizio));
    QPolarChart *pChart = new QPolarChart();

    /*QAreaSeries* firstDayArea = new QAreaSeries(seriesFirstDay);
    firstDayArea->setColor(QColor::fromRgba(qRgba(0,255,0,128)));
    firstDayArea->setName("Primo giorno");

    QAreaSeries* lastDayArea = new QAreaSeries(seriesLastDay);
    lastDayArea->setColor(QColor::fromRgba(qRgba(255,0,0,128)));
    lastDayArea->setName("Ultimo giorno");

    QAreaSeries* rifArea = new QAreaSeries(valRiferimento);
    rifArea->setColor(QColor::fromRgba(qRgba(0,0,255,128)));
    rifArea->setName("Valori di riferimento");*/

    pChart->addSeries(seriesFirstDay);
    pChart->addSeries(seriesLastDay);
    pChart->addSeries(valRiferimento);

    //asse radiale
    QValueAxis *ugm3 = new QValueAxis;
    ugm3->setRange(0, 100);
    ugm3->setTickCount(7);
    ugm3->setLabelsVisible(false);
    pChart->addAxis(ugm3, QPolarChart::PolarOrientationRadial);

    // asse azimutale
    QCategoryAxis *componenti = new QCategoryAxis();
    componenti->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    componenti->setRange(0, 360);
    componenti->setLabelsVisible(true);
    pChart->addAxis(componenti, QPolarChart::PolarOrientationAngular);

    for(int i=0;i<comp.size();i++){
        componenti->append(comp.at(i),360/comp.size()*i);
    }

    seriesFirstDay->attachAxis(componenti);
    seriesFirstDay->attachAxis(ugm3);

    seriesLastDay->attachAxis(componenti);
    seriesLastDay->attachAxis(ugm3);

    valRiferimento->attachAxis(componenti);
    valRiferimento->attachAxis(ugm3);

    this->setChart(pChart);

}

void MyChartView::scatterChart() {
    resetView();
    emit chartPronto();
    //MyChartView::show();

    QList<QMap<QString, double>> dati = data.getDati();
    QString singleComp = *comp.begin();

    QScatterSeries* sSerie = new QScatterSeries();
    sSerie->setMarkerSize(10);
    sSerie->setName(singleComp);

    for(auto riga:dati) {
        sSerie->append(QPointF((Dati::getDateFromDouble(riga.value("Data")).time().msecsSinceStartOfDay())/3600000, riga.value(singleComp)));
    }

    // asse X
    //asseX = new QtCharts::QDateTimeAxis;
    //asseX->setFormat("h:mm");
    QtCharts::QValueAxis* asseX2 = new QtCharts::QValueAxis();
    asseX2->setTickCount(24);
    this->chart()->addAxis(asseX2, Qt::AlignBottom);

    // asse Y
    asseY = new QtCharts::QValueAxis();
    // lascio spazio sopra l'ultimo pallino
    asseY->setRange(0, maxFromSerie(sSerie)+(maxFromSerie(sSerie)/sSerie->markerSize()));
    qDebug()<<maxFromSerie(sSerie);
    this->chart()->addAxis(asseY, Qt::AlignLeft);

    this->chart()->addSeries(sSerie);
    sSerie->attachAxis(asseX2);
    sSerie->attachAxis(asseY);
}

void MyChartView::resetView(){
    QtCharts::QChart* graf = this->chart();
    this->setChart(new QtCharts::QChart());
    delete graf;
}

QLineSeries* MyChartView::sommaY(QLineSeries *upper, QLineSeries *lower) const {
    QVector<QPointF> puntiLower = lower->pointsVector();
    QVector<QPointF> puntiUpper = upper->pointsVector();

    for(int i=0;i<puntiLower.size();++i){
        puntiUpper[i].setY(puntiLower.at(i).y()+puntiUpper.at(i).y());
    }
    upper->replace(puntiUpper);
    return upper;
}

double MyChartView::maxValueFromListSeries(QList<QtCharts::QLineSeries*> series) {
    double max=0;

    for(auto serie:series) {
        if(maxFromSerie(serie)>max)
            max=maxFromSerie(serie);
    }

    return max;
}

double MyChartView::maxFromSerie(QtCharts::QXYSeries* serie) {
    double max=0;

    for(unsigned int i=0; i<serie->count(); ++i) {
        if(serie->at(i).y()>max) {
            max = serie->at(i).y();
        }
    }

    return max;
}
