#include "../include/Box.hpp"
#include "../include/Plane.hpp"

void Box::generate(float size, int divisions)
{
    float divisionLength = size / (float)divisions;
    float radius = size / 2.0;

    float divisionSize, currentdivision;
    int i, j, k;
    Point p1, p2, p3, p4;

    float z_axis = size / 2;
    float x_axis = -(size / 2);
    float y_axis = -(size / 2);

    Point bottom_normal(0.0, -1.0, 0.0);
    Point upper_normal(0.0, 1.0, 0.0);

    for (i = 0; i < divisions; i++)
    {

        divisionSize = -radius + i * divisionLength;
        for (j = 0; j < divisions; j++)
        {
            // Create the bottom face of the box
            currentdivision = radius - j * divisionLength;
            p1 = Point(divisionSize, -radius, currentdivision);
            p2 = Point(divisionSize + divisionLength, -radius, currentdivision);
            p3 = Point(divisionSize + divisionLength, -radius, currentdivision - divisionLength);

            // p1 e p3
            p4 = Point(divisionSize, -radius, currentdivision - divisionLength);

            this->addPoint(p1);
            this->addPoint(p3);
            this->addPoint(p2);

            this->addPoint(p1);
            this->addPoint(p4);
            this->addPoint(p3);

            for (k = 0; k < 6; k++)
            {
                this->addNormal(bottom_normal);
            }

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));
            // Create the top face of the box
            p1 = Point(divisionSize, radius, currentdivision);
            p2 = Point(divisionSize + divisionLength, radius, currentdivision);
            p3 = Point(divisionSize + divisionLength, radius, currentdivision - divisionLength);

            // p1 e p3
            p4 = Point(divisionSize, radius, currentdivision - divisionLength);

            // t1 = Triangle(p1, p2, p3);
            // t2 = Triangle(p1, p3, p4);
            // addTriangle(t1);
            // addTriangle(t2);
            this->addPoint(p1);
            this->addPoint(p2);
            this->addPoint(p3);

            this->addPoint(p1);
            this->addPoint(p3);
            this->addPoint(p4);

            for (k = 0; k < 6; k++)
            {
                this->addNormal(upper_normal);
            }

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + (j * divisionLength), size));
        }
    }

    Point left_normal(0.0, 0.0, 1.0);
    Point right_normal(0.0, 0.0, -1.0);
    // Create the left face of the box
    for (i = 0; i < divisions; i++)
    {
        divisionSize = -radius + i * divisionLength;
        for (j = 0; j < divisions; j++)
        {
            currentdivision = radius - j * divisionLength;
            p1 = Point(divisionSize, currentdivision, -radius);
            p2 = Point(divisionSize + divisionLength, currentdivision, -radius);
            p3 = Point(divisionSize + divisionLength, currentdivision - divisionLength, -radius);
            p4 = Point(divisionSize, currentdivision - divisionLength, -radius);

            // p1 e p3

            // t1 = Triangle(p1, p2, p3);
            // t2 = Triangle(p1, p3, p4);
            // addTriangle(t1);
            // addTriangle(t2);
            this->addPoint(p1);
            this->addPoint(p2);
            this->addPoint(p3);

            this->addPoint(p1);
            this->addPoint(p3);
            this->addPoint(p4);

            for (k = 0; k < 6; k++)
            {
                this->addNormal(left_normal);
            }

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + (j * divisionLength), size));

            // Create the right face of the box
            p1 = Point(divisionSize, currentdivision, radius);
            p2 = Point(divisionSize + divisionLength, currentdivision, radius);
            p3 = Point(divisionSize + divisionLength, currentdivision - divisionLength, radius);

            // p1 e p3
            p4 = Point(divisionSize, currentdivision - divisionLength, radius);

            // t1 = Triangle(p2, p1, p3);
            // t2 = Triangle(p3, p1, p4);
            // addTriangle(t1);
            // addTriangle(t2);
            this->addPoint(p1);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addPoint(p3);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addPoint(p2);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), size));

            this->addPoint(p1);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + (j * divisionLength), size));

            this->addPoint(p4);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(z_axis - ((i + 1) * divisionLength), x_axis + (j * divisionLength), size));

            this->addPoint(p3);
            this->addNormal(right_normal);
            this->addTextureP(generateTextures(z_axis - (i * divisionLength), x_axis + ((j + 1) * divisionLength), size));
        }
    }

    Point front_normal(1.0, 0.0, 0.0);
    Point back_normal(-1.0, 0.0, 0.0);

    // Create the front face of the box
    for (i = 0; i < divisions; i++)
    {
        divisionSize = -radius + i * divisionLength;
        for (j = 0; j < divisions; j++)
        {
            currentdivision = radius - j * divisionLength;
            p1 = Point(radius, currentdivision, divisionSize);
            p2 = Point(radius, currentdivision, divisionSize + divisionLength);
            p3 = Point(radius, currentdivision - divisionLength, divisionSize + divisionLength);

            // p1 e p3
            p4 = Point(radius, currentdivision - divisionLength, divisionSize);

            // t1 = Triangle(p1, p2, p3);
            // t2 = Triangle(p1, p3, p4);
            // addTriangle(t1);
            // addTriangle(t2);
            this->addPoint(p1);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(z_axis - (j * divisionLength), x_axis + (i * divisionLength), size));

            this->addPoint(p2);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(z_axis - (j * divisionLength), x_axis + ((i + 1) * divisionLength), size));

            this->addPoint(p3);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(z_axis - ((j + 1) * divisionLength), x_axis + ((i + 1) * divisionLength), size));

            this->addPoint(p1);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(z_axis - (j * divisionLength), x_axis + (i * divisionLength), size));

            this->addPoint(p3);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(z_axis - ((j + 1) * divisionLength), x_axis + ((i + 1) * divisionLength), size));

            this->addPoint(p4);
            this->addNormal(front_normal);
            this->addTextureP(generateTextures(z_axis - ((j + 1) * divisionLength), x_axis + (i * divisionLength), size));

            // Create the back face of the box
            p1 = Point(-radius, currentdivision, divisionSize);
            p2 = Point(-radius, currentdivision, divisionSize + divisionLength);
            p3 = Point(-radius, currentdivision - divisionLength, divisionSize + divisionLength);

            // p1 e p3
            p4 = Point(-radius, currentdivision - divisionLength, divisionSize);

            // t1 = Triangle(p2, p1, p3);
            // t2 = Triangle(p3, p1, p4);
            // addTriangle(t1);
            // addTriangle(t2);
            this->addPoint(p1);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(z_axis - (j * divisionLength), x_axis + (i * divisionLength), size));

            this->addPoint(p3);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(z_axis - ((j + 1) * divisionLength), x_axis + ((i + 1) * divisionLength), size));

            this->addPoint(p2);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(z_axis - (j * divisionLength), x_axis + ((i + 1) * divisionLength), size));

            this->addPoint(p1);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(z_axis - (j * divisionLength), x_axis + (i * divisionLength), size));

            this->addPoint(p4);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(z_axis - ((j + 1) * divisionLength), x_axis + (i * divisionLength), size));

            this->addPoint(p3);
            this->addNormal(back_normal);
            this->addTextureP(generateTextures(z_axis - ((j + 1) * divisionLength), x_axis + ((i + 1) * divisionLength), size));
        }
    }
}

Point Box::generateTextures(float a, float b, float max)
{
    float x = (a + max / 2) / max;
    float y = (b + max / 2) / max;

    return Point(y, x, 0);
}