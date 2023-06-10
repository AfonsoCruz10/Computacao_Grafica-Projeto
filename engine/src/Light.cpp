#include "../include/Light.hpp"

Light::Light()
{
}

void Light::setPos(float x, float y, float z, float dirOrPoint)
{
    pos[0] = x;
    pos[1] = y;
    pos[2] = z;
    pos[3] = dirOrPoint;
}

void Light::setDir(float x, float y, float z)
{
    dir[0] = x;
    dir[1] = y;
    dir[2] = z;
}

void Light::setCutoff(float value)
{
    cutoff = value;
}

void Light::setType(int value)
{
    type = value;
}

int Light::getType()
{
    return type;
}

float *Light::getPos()
{
    return pos;
}

float *Light::getDir()
{
    return dir;
}

float Light::getCutoff()
{
    return cutoff;
}