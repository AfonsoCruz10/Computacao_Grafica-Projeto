#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Shape.hpp"

class Sphere : public Shape
{
public:
    void generate(float, int, int);
    Point generateTextures(float, float);
};

#endif