#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <fstream>

class Point
{
private:
    float x, y, z;

public:
    Point(float, float, float);
    Point(float, float);
    Point();
    
    float getx();
    float gety();
    float getz();
    void setx(float);
    void sety(float);
    void setz(float);

    void negative();

    void serialize(std::ofstream *);

    Point subPoint(Point v);
    void cross(Point v);
    Point normalize();
    Point normalizeB(Point v1, Point v2);
};

#endif // ponto