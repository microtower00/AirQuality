#include "coordinate.h"

Coordinate::Coordinate(double lat, double lon):QPair<double,double>{lat,lon}{}
Coordinate::Coordinate(const Coordinate& coord):QPair{coord.latitude(),coord.longitude()}{}

double Coordinate::latitude() const{
    return first;
}

double Coordinate::longitude() const{
    return second;
}
