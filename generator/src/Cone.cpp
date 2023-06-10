#include "../include/Cone.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

void Cone::generate(float size, float high, int slices, int stacks)
{
    float stackDistance = high / stacks;
    float stackSize = size / stacks;
    float stackAngle = 2 * M_PI / slices;
    int i, j;
    float y1, y2, sliceRadius1, sliceRadius2, angle1, angle2;
    Point p1, p2, p3, p4;
    Point t1, t2, t3, t4;
    Point n1, n2, n3, n4;
    // the cone
    for (i = 0; i < stacks; i++)
    {
        for (j = 0; j < slices; j++)
        {
            y1 = high - i * stackDistance;
            sliceRadius1 = size - (stacks - i) * stackSize;
            angle1 = j * stackAngle;

            i++;
            j++;
            y2 = high - i * stackDistance;
            sliceRadius2 = size - (stacks - i) * stackSize;
            angle2 = j * stackAngle;
            j--;
            i--;

            p1 = Point(sin(angle1) * sliceRadius1, y1, cos(angle1) * sliceRadius1);
            p2 = Point(sin(angle1) * sliceRadius2, y2, cos(angle1) * sliceRadius2);
            p3 = Point(sin(angle2) * sliceRadius2, y2, cos(angle2) * sliceRadius2);
            p4 = Point(sin(angle2) * sliceRadius1, y1, cos(angle2) * sliceRadius1);

            t1 = generateTextures(p1.getx(), p1.gety(), p1.getz(), high);
            t2 = generateTextures(p2.getx(), p2.gety(), p2.getz(), high);
            t3 = generateTextures(p3.getx(), p3.gety(), p3.getz(), high);
            t4 = generateTextures(p4.getx(), p4.gety(), p4.getz(), high);

            n1 = Point(p1.getx(), p1.gety(), p1.getz()).normalize();
            n2 = Point(p2.getx(), p2.gety(), p2.getz()).normalize();
            n3 = Point(p3.getx(), p3.gety(), p3.getz()).normalize();
            n4 = Point(p4.getx(), p4.gety(), p4.getz()).normalize();

            this->addPoint(p1);
            this->addTextureP(t1);
            this->addNormal(n1);
            this->addPoint(p2);
            this->addTextureP(t2);
            this->addNormal(n2);
            this->addPoint(p3);
            this->addTextureP(t3);
            this->addNormal(n3);

            this->addPoint(p1);
            this->addTextureP(t1);
            this->addNormal(n1);
            this->addPoint(p3);
            this->addTextureP(t3);
            this->addNormal(n3);
            this->addPoint(p4);
            this->addTextureP(t4);
            this->addNormal(n4);

            if (i == stacks - 1)
            {
                p1 = Point(0, 0, 0);
                t1 = generateTextures(p1.getx(), p1.gety(), p1.getz(), high);

                n1 = Point(0, -high / size * stackSize / stackDistance, -high / size * stackSize / stackDistance).normalize();

                this->addPoint(p2);
                this->addTextureP(t2);
                this->addNormal(n2);
                this->addPoint(p1);
                this->addTextureP(t1);
                this->addNormal(n1);
                this->addPoint(p3);
                this->addTextureP(t3);
                this->addNormal(n3);
            }
        }
    }
}
Point Cone::generateTextures(float x, float y, float z, float height)
{
    float theta = atan2(z, x);
    float u = (theta + M_PI) / (2 * M_PI);
    float v = y / height;
    return Point(u, v);
}