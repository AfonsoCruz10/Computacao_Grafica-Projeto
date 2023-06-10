#ifndef BOX_HPP
#define BOX_HPP

#include "Shape.hpp"

class Box : public Shape
{
public:
    void generate(float, int);
    Point generateTextures(float, float, float);
};

#endif