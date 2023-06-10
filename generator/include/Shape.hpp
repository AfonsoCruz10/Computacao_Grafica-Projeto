#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Point.hpp"

#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

class Shape
{
protected:
    vector<Point> points;
    vector<Point> normals;
    vector<Point> textures;

public:
    Shape();
    Shape(vector<Point>);
    void addPoint(Point);
    void addNormal(Point);
    void addTextureP(Point);
    vector<Point> getPoints();
    vector<float> getVBO();
    void serialize(string);
    Point getPoint(int);
};
#endif