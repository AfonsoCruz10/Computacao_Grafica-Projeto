#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <math.h>
#include <vector>
#include <GL/glut.h>
#include "../../generator/include/Point.hpp"

using namespace std;

class Transformation
{
private:
    char type;
    float angle, x, y, z;
    float time = 0.0;
    int id = 0; // Static or dynamic

    bool drawCurves = true;
    bool align = false;
    float tg = 0;
    int frame = 0;
    float yt[3] = {0, 1, 0};
    vector<Point> points;

public:
    Transformation();
    Transformation(char, float, float, float);
    Transformation(float, float, float, float);

    float getAngle();
    float getX();
    float getY();
    float getZ();
    char getType();
    void setType(char);
    void setTime(float);
    void setID(int);
    void setAlign(bool);
    void addPoint(Point);

    void getGlobalCatmullRomPoint(float, float *, float *);
    void getCatmullRomPoint(float, Point, Point, Point, Point, float *, float *);
    void multMatrixVector(float *, float *, float *);

    void cross(float *, float *, float *);
    void normalize(float *);
    void buildRotMatrix(float *, float *, float *, float *);

    void apply(float);
};

#endif