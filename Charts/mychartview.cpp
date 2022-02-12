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

MyChartView::MyChartView (Dati *d) : data (d)
{
    MASSIMICONSENTITI.insert ("co", MAXCO);
    MASSIMICONSENTITI.insert ("so2", MAXSO2);
    MASSIMICONSENTITI.insert ("nh3", MAXNH3);
    MASSIMICONSENTITI.insert ("no", MAXNO);
    MASSIMICONSENTITI.insert ("no2", MAXNO2);
    MASSIMICONSENTITI.insert ("o3", MAXO3);
    MASSIMICONSENTITI.insert ("pm10", MAXPM10);
    MASSIMICONSENTITI.insert ("pm2_5", MAXPM2_5);

    this->setRenderHint (QPainter::Antialiasing);
    setRubberBand (MyChartView::HorizontalRubberBand);
}

void
MyChartView::setCompScelti (const QStringList &compScelti)
{
    comp = compScelti;
}

void
MyChartView::lineChart ()
{
    resetView ();
    emit chartPronto ();
    emit tipoChartPronto (MyChart::GraphType::LineG);
    QMap<QString, QtCharts::QAbstractSeries *> series;

    for (QString chiave : comp)
        {
            series.insert (chiave, new MyLineSeries (data, chiave));
        }

    this->setChart (new MyChart (series, MyChart::GraphType::LineG));
}

void
MyChartView::areaChart ()
{
    resetView ();
    emit chartPronto ();
    emit tipoChartPronto (MyChart::GraphType::AreaG);
    QMap<QString, QtCharts::QAbstractSeries *> series;

    for (QString chiave : comp)
        {
            series.insert (chiave, new MyLineSeries (data, chiave));
        }

    this->setChart (new MyChart (series, MyChart::GraphType::AreaG));
}

void
MyChartView::barChart ()
{
    resetView ();

    MyBarSeries *serie = new MyBarSeries (data, comp);
    QMap<QString, QAbstractSeries *> param;
    param.insert ("Serie di barre", serie);
    MyChart *barChart = new MyChart (param, MyChart::GraphType::BarG);
    setChart (barChart);

    emit chartPronto ();
    emit tipoChartPronto (MyChart::GraphType::BarG);
}

void
MyChartView::radarChart ()
{
    resetView ();
    setRubberBand (MyChartView::NoRubberBand);
    QMap<QString, QAbstractSeries *> series;
    QList<QMap<QString, double> > datiElab, datiGrezzi = data->getDati ();
    QList<QMap<QString, double> > datiFirstDay, datiLastDay;
    QMap<QString, double> mediaFirstDay, mediaLastDay;

    datiElab.push_back (MASSIMICONSENTITI);
    for (auto record : datiGrezzi)
        {
            if (record.value ("Data") == datiGrezzi.first ().value ("Data"))
                datiFirstDay.push_back (record);
            if (record.value ("Data") == datiGrezzi.last ().value ("Data"))
                datiLastDay.push_back (record);
        }

    for (auto record : datiFirstDay)
        {
            for (QString componente : comp)
                {
                    mediaFirstDay.insert (componente,
                                          mediaFirstDay.value (componente)
                                              + record.value (componente) / 2);
                }
        }

    for (auto record : datiLastDay)
        {
            for (QString componente : comp)
                {
                    mediaLastDay.insert (componente,
                                         mediaLastDay.value (componente)
                                             + record.value (componente) / 2);
                }
        }

    datiElab.push_back (mediaFirstDay);
    datiElab.push_back (mediaLastDay);

    QMap<QString, double> fondoScala
        = MyPolarSeries::calcolaFondoScala (datiElab);
    QString nomeserie;
    for (QMap<QString, double> entry : datiElab)
        {
            nomeserie = entry == mediaFirstDay
                            ? "Primo giorno"
                            : entry == mediaLastDay ? "Ultimo giorno"
                                                    : "Val. di riferimento";
            series.insert (nomeserie,
                           new MyPolarSeries (entry, fondoScala, comp));
        }

    MyPolarChart *pChart = new MyPolarChart (series);
    QtCharts::QCategoryAxis *componenti = dynamic_cast<QCategoryAxis *> (
        pChart->axes (QtCharts::QPolarChart::PolarOrientationAngular).at (0));

    for (int i = 0; i < comp.size (); i++)
        {
            componenti->append (comp.at (i), 360 / comp.size () * i);
        }

    setChart (pChart);

    emit chartPronto ();
    emit tipoChartPronto (MyChart::GraphType::RadarG);
}

void
MyChartView::scatterChart ()
{
    resetView ();
    setRubberBand (MyChartView::NoRubberBand);
    QString singleComp = comp.first ();

    MyScatterSerie *sSerie = new MyScatterSerie (data, singleComp);
    sSerie->setMarkerSize (10);
    sSerie->setName (singleComp);

    QMap<QString, QAbstractSeries *> param;
    param.insert (singleComp, sSerie);
    setChart (new MyChart (param, MyChart::GraphType::ScatterG));

    emit chartPronto ();
    emit tipoChartPronto (MyChart::GraphType::ScatterG);
}

void
MyChartView::resetView ()
{
    QtCharts::QChart *graf = this->chart ();
    this->setChart (new QtCharts::QChart ());
    delete graf;
}
