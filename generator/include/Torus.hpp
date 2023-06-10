#ifndef TORUS_HPP
#define TORUS_HPP

#include <math.h>
#include "Shape.hpp"

class Torus : public Shape
{
public:
    Torus() : Shape(){};

    Torus(vector<Point> pointp) : Shape(pointp){};

    void generate(float, float, int, int);
};

#endif // TORUS_HPP