#ifndef BEZIER_HPP
#define BEZIER_HPP

#include "Shape.hpp"
#include <string>
#include <fstream>
#include <iostream>

class Bezier : public Shape
{
private:
    vector<Shape> patches;

    Point bezierPatch(float u, float v, Shape patch);
    Point bValue(float u, Point p0, Point p1, Point p2, Point p3);

public:
    void parseBezier(const char *inputFile);
    void bezierPoints(int tessellation);
};

#endif // BEZIER_H