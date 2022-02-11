#ifndef COORDINATE_H
#define COORDINATE_H

#include <QPair>

class Coordinate : public QPair<double,double>
{
public:
    Coordinate(double lat = 0, double lon = 0);
    Coordinate(const Coordinate&);
    double latitude()const;
    double longitude()const;

};

#endif // COORDINATE_H
