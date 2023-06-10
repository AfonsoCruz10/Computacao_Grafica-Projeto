#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include <fstream>

#include "Point.hpp"

class Triangle
{
private:
    Point p1, p2, p3;

public:
    Triangle(Point, Point, Point);
    Triangle();

    Point getp1();
    Point getp2();
    Point getp3();
    void serialize(std::ofstream *);
};

#endif //            TRIANGLE_HPP
