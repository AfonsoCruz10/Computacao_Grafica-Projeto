#include "../include/Plane.hpp"

void Plane::generate(float length, int divisions)
{
    Point normal(0.0, 1.0, 0.0);

    float divisionSize = length / (float)divisions;
    float r = (float)length / 2.0;

    float z_axis = length / 2;
    float x_axis = -(length / 2);

    for (int i = 0; i < divisions; i++)
    {
        float xp = -r + i * divisionSize;
        for (int j = 0; j < divisions; j++)
        {
            float z = r - j * divisionSize;
            Point p1(xp, 0, z);
            Point p2(xp + divisionSize, 0, z);
            Point p3(xp + divisionSize, 0, z - divisionSize);

            // p1 e p3
            Point p4(xp, 0, z - divisionSize);

            // Triangle t1(p1, p2, p3), t2(p1, p3, p4);
            // addTriangle(t1);
            // addTriangle(t2);

            this->addPoint(p1);
            this->addNormal(normal);
            this->addTextureP(Point((x_axis + (j * divisionSize)) / length, z_axis - (i * divisionSize) / length));

            this->addPoint(p2);
            this->addNormal(normal);
            this->addTextureP(Point((x_axis + ((j + 1) * divisionSize)) / length, z_axis - (i * divisionSize) / length));

            this->addPoint(p3);
            this->addNormal(normal);
            this->addTextureP(Point((x_axis + ((j + 1) * divisionSize)) / length, z_axis - ((i + 1) * divisionSize) / length));

            this->addPoint(p1);
            this->addNormal(normal);
            this->addTextureP(Point((x_axis + (j * divisionSize)) / length, z_axis - (i * divisionSize) / length));

            this->addPoint(p3);
            this->addNormal(normal);
            this->addTextureP(Point((x_axis + ((j + 1) * divisionSize)) / length, z_axis - ((i + 1) * divisionSize) / length));

            this->addPoint(p4);
            this->addNormal(normal);
            this->addTextureP(Point((x_axis + (j * divisionSize)) / length, z_axis - ((i + 1) * divisionSize) / length));
        }
    }
}
