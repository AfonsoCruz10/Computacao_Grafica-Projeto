#include "../include/Camera.hpp"

#include <math.h>

Camera::Camera()
{
    this->camX = 5.0;
    this->camY = 10.0;
    this->camZ = 5.0;

    this->camLookX = 0.0;
    this->camLookY = 0.0;
    this->camLookZ = 0.0;

    this->UPx = 0.0;
    this->UPy = 1.0;
    this->UPz = 0.0;

    this->fov = 45.0f;
    this->near = 1.0;
    this->far = 1000.0f;

    this->beta = -0.8;
    this->alpha = -1.7;
}

// Getters

float Camera::getcamX()
{
    return camX;
}

float Camera::getcamY()
{
    return camY;
}

float Camera::getcamZ()
{
    return camZ;
}

float Camera::getcamLookX()
{
    return camLookX;
}

float Camera::getcamLookY()
{
    return camLookY;
}

float Camera::getcamLookZ()
{
    return camLookZ;
}

float Camera::getUPx()
{
    return UPx;
}

float Camera::getUPy()
{
    return UPy;
}

float Camera::getUPz()
{
    return UPz;
}

float Camera::getFov()
{
    return fov;
}

float Camera::getNear()
{
    return near;
}

float Camera::getFar()
{
    return far;
}

float Camera::getRaio()
{
    return raio;
}

float Camera::getAlpha()
{
    return alpha;
}

float Camera::getBeta()
{
    return beta;
}

void Camera::setcamX(float x)
{
    this->camX = x;
}

void Camera::setcamY(float y)
{
    this->camY = y;
}

void Camera::setcamZ(float z)
{
    this->camZ = z;
}

void Camera::setcamLookX(float x)
{
    this->camLookX = x;
}

void Camera::setcamLookY(float y)
{
    this->camLookY = y;
}

void Camera::setcamLookZ(float z)
{
    this->camLookZ = z;
}

void Camera::setUPx(float x)
{
    this->UPx = x;
}

void Camera::setUPy(float y)
{
    this->UPy = y;
}

void Camera::setUPz(float z)
{
    this->UPz = z;
}

void Camera::setFov(float new_fov)
{
    this->fov = new_fov;
}

void Camera::setNear(float new_near)
{
    this->near = new_near;
}

void Camera::setFar(float new_far)
{
    this->far = new_far;
}

void Camera::setRaio(float r)
{
    raio = r;
}

void Camera::setAlpha(float a)
{
    alpha = a;
}

void Camera::setBeta(float b)
{
    beta = b;
}

void Camera::convert()
{

    camX = raio * cos(beta) * sin(alpha);
    camY = raio * sin(beta);
    camZ = raio * cos(beta) * cos(alpha);
}

void Camera::UpdateRaio()
{
    raio = sqrt(camX * camX + camY * camY + camZ * camZ);
}

void Camera::spherical2Cartesian()
{
    camX = centerX + raio * cos(beta) * sin(alpha);
    camY = centerY + raio * sin(beta);
    camZ = centerZ + raio * cos(beta) * cos(alpha);
}