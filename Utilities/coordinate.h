#ifndef COORDINATE_H
#define COORDINATE_H

#include <QPair>

class Coordinate : public QPair<double,double>
{
private:
    QPair<double,double> coords;
public:
    Coordinate(double lat = 0, double lon = 0);
    Coordinate(const Coordinate&);
    Coordinate& operator=(const Coordinate& c2) =default;

    double latitude() const;
    double longitude() const;
};

#endif // COORDINATE_H
