#include "../include/Sphere.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

void Sphere::generate(float radius, int slices, int stacks)
{
    float angleStacks = M_PI / stacks;
    float angleSlices = (2 * M_PI) / slices;

    float rectAngle = (M_PI / 2);
    float beta;
    float alpha;

    for (int j = 0; j < stacks; j++)
    {
        beta = j * angleStacks - rectAngle;

        for (int i = 0; i < slices; i++)
        {
            alpha = i * angleSlices;

            Point v1(radius * cos(alpha) * cos(beta), radius * sin(beta), radius * sin(alpha) * cos(beta));
            Point v2(radius * cos(alpha) * cos(beta + angleStacks), radius * sin(beta + angleStacks), radius * sin(alpha) * cos(beta + angleStacks));
            Point v3(radius * cos(alpha + angleSlices) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSlices) * cos(beta));

            // Triangle t1(v1, v2, v3);
            // this->addTriangle(t1);
            this->addPoint(v1);
            this->addNormal(v1.normalize());
            this->addTextureP(generateTextures(alpha, beta));

            this->addPoint(v2);
            this->addNormal(v2.normalize());
            this->addTextureP(generateTextures(alpha, beta + angleStacks));

            this->addPoint(v3);
            this->addNormal(v3.normalize());
            this->addTextureP(generateTextures(alpha + angleSlices, beta));

            Point v4(radius * cos(alpha) * cos(beta + angleStacks), radius * sin(beta + angleStacks), radius * sin(alpha) * cos(beta + angleStacks));
            Point v5(radius * cos(alpha + angleSlices) * cos(beta + angleStacks), radius * sin(beta + angleStacks), radius * sin(alpha + angleSlices) * cos(beta + angleStacks));
            Point v6(radius * cos(alpha + angleSlices) * cos(beta), radius * sin(beta), radius * sin(alpha + angleSlices) * cos(beta));

            this->addPoint(v4);
            this->addNormal(v4.normalize());
            this->addTextureP(generateTextures(alpha, beta + angleStacks));

            this->addPoint(v5);
            this->addNormal(v5.normalize());
            this->addTextureP(generateTextures(alpha + angleSlices, beta + angleStacks));

            this->addPoint(v6);
            this->addNormal(v6.normalize());
            this->addTextureP(generateTextures(alpha + angleSlices, beta));
            // Triangle t2(v4, v5, v6);
            // this->addTriangle(t2);
        }
    }
}

Point Sphere::generateTextures(float alpha, float beta)
{
    float du = (1.0 / (2.0 * M_PI)) * (-alpha) + 1.0;
    float dy = (1.0 / M_PI) * (beta + (M_PI / 2.0));

    return Point(du, dy);
}