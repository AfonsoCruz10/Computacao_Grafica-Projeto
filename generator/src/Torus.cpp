#define _USE_MATH_DEFINES
#include "../include/Torus.hpp"

void Torus::generate(float inRadius, float outRadius, int slices, int layers)
{
    float alpha, nextAlpha, beta, nextBeta;
    float sliceAngle = 2 * M_PI / slices;
    float layerAngle = 2 * M_PI / layers;

    for (int i = 0; i < layers; i++)
    {
        beta = i * layerAngle;
        nextBeta = (i + 1) * layerAngle;

        for (int j = 0; j < slices; j++)
        {
            alpha = j * sliceAngle;
            nextAlpha = (j + 1) * sliceAngle;

            this->addPoint(Point((outRadius + inRadius * cos(nextBeta)) * cos(alpha),
                                 (outRadius + inRadius * cos(nextBeta)) * sin(alpha),
                                 inRadius * sin(nextBeta)));
            this->addNormal(Point((1 + 1 * cos(nextBeta)) * cos(alpha),
                                  (1 + 1 * cos(nextBeta)) * sin(alpha),
                                  1 * sin(nextBeta)));
            this->addTextureP(Point((-i * (1.0 / layers)) + 1, j * 1.0 / slices));

            this->addPoint(Point((outRadius + inRadius * cos(beta)) * cos(alpha),
                                 (outRadius + inRadius * cos(beta)) * sin(alpha),
                                 inRadius * sin(beta)));
            this->addNormal(Point((1 + 1 * cos(beta)) * cos(alpha),
                                  (1 + 1 * cos(beta)) * sin(alpha),
                                  1 * sin(beta)));
            this->addTextureP(Point((-i * (1.0 / layers)) + 1, (j + 1) * 1.0 / slices));

            this->addPoint(Point((outRadius + inRadius * cos(nextBeta)) * cos(nextAlpha),
                                 (outRadius + inRadius * cos(nextBeta)) * sin(nextAlpha),
                                 inRadius * sin(nextBeta)));
            this->addNormal(Point((1 + 1 * cos(nextBeta)) * cos(nextAlpha),
                                  (1 + 1 * cos(nextBeta)) * sin(nextAlpha),
                                  1 * sin(nextBeta)));
            this->addTextureP(Point((-(i + 1) * (1.0 / layers)) + 1, j * 1.0 / slices));

            this->addPoint(Point((outRadius + inRadius * cos(nextBeta)) * cos(nextAlpha),
                                 (outRadius + inRadius * cos(nextBeta)) * sin(nextAlpha),
                                 inRadius * sin(nextBeta)));
            this->addNormal(Point((1 + 1 * cos(nextBeta)) * cos(nextAlpha),
                                  (1 + 1 * cos(nextBeta)) * sin(nextAlpha),
                                  1 * sin(nextBeta)));
            this->addTextureP(Point((-i * (1.0 / layers)) + 1, (j + 1) * 1.0 / slices));

            this->addPoint(Point((outRadius + inRadius * cos(beta)) * cos(alpha),
                                 (outRadius + inRadius * cos(beta)) * sin(alpha),
                                 inRadius * sin(beta)));
            this->addNormal(Point((1 + 1 * cos(beta)) * cos(alpha),
                                  (1 + 1 * cos(beta)) * sin(alpha),
                                  1 * sin(beta)));
            this->addTextureP(Point((-(i + 1) * (1.0 / layers)) + 1, (j + 1) * 1.0 / slices));

            this->addPoint(Point((outRadius + inRadius * cos(beta)) * cos(nextAlpha),
                                 (outRadius + inRadius * cos(beta)) * sin(nextAlpha),
                                 inRadius * sin(beta)));
            this->addNormal(Point((1 + 1 * cos(beta)) * cos(nextAlpha),
                                  (1 + 1 * cos(beta)) * sin(nextAlpha),
                                  1 * sin(beta)));
            this->addTextureP(Point((-(i + 1) * (1.0 / layers)) + 1, j * 1.0 / slices));
        }
    }
}