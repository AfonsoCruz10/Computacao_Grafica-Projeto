#ifndef CONE_HPP
#define CONE_HPP

#include "Shape.hpp"

class Cone : public Shape
{
public:
    void generate(float, float, int, int);
    Point generateTextures(float, float, float, float);
};

#endif