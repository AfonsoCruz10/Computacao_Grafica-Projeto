#include "../include/Point.hpp"
#include <math.h>

Point::Point(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(float xp, float yp)
{
    x = xp;
    y = yp;
    z = 0;
}

Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

float Point::getx()
{
    return this->x;
}

float Point::gety()
{
    return this->y;
}

float Point::getz()
{
    return this->z;
}

void Point::setx(float xx)
{
    this->x = xx;
}

void Point::sety(float yy)
{
    this->y = yy;
}

void Point::setz(float zz)
{
    this->z = zz;
}

void Point::negative()
{
    this->x = -(this->x);
    this->y = -(this->y);
    this->z = -(this->z);
}

void Point::serialize(std::ofstream *pontos)
{
    *pontos << x << " , " << y << " , " << z;
}

Point Point::normalize()
{
    float vectorLength = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    return Point(x / vectorLength, y / vectorLength, z / vectorLength);
}

Point Point::normalizeB(Point v1, Point v2)
{
    Point aux(x, y, z);
    Point v3, v4;

    v3 = aux.subPoint(v1);
    v4 = aux.subPoint(v2);

    v3.cross(v4);
    v3.normalize();

    return v3;
}

Point Point::subPoint(Point v)
{
    float x1, y1, z1;

    x1 = x - v.getx();
    y1 = y - v.gety();
    z1 = z - v.getz();

    return Point(x1, y1, z1);
}

void Point::cross(Point v)
{
    float auxX = x, auxY = y, auxZ = z;

    x = auxY * v.getz() - auxZ * v.gety();
    y = auxZ * v.getx() - auxX * v.getz();
    z = auxX * v.gety() - auxY * v.getx();
}