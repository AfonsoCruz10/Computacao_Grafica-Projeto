#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

class Camera
{
private:
    float camX;
    float camY;
    float camZ;

    float camLookX;
    float camLookY;
    float camLookZ;

    float UPx;
    float UPy;
    float UPz;

    float fov;
    float near;
    float far;

    float alpha = 0.0;
    float beta = 0.0;
    float raio = 10.0;

public:
    float centerX = 0, centerY = 0, centerZ = 0;
    Camera();
    void spherical2Cartesian();
    void convert();
    void UpdateRaio();

    void setcamX(float x);
    void setcamY(float y);
    void setcamZ(float z);

    void setcamLookX(float x);
    void setcamLookY(float y);
    void setcamLookZ(float z);

    void setUPx(float x);
    void setUPy(float y);
    void setUPz(float z);

    void setFov(float new_fov);
    void setNear(float new_near);
    void setFar(float new_far);

    void setAlpha(float new_alpha);
    void setBeta(float new_beta);
    void setRaio(float);

    float getcamX();
    float getcamY();
    float getcamZ();

    float getcamLookX();
    float getcamLookY();
    float getcamLookZ();

    float getUPx();
    float getUPy();
    float getUPz();

    float getFov();
    float getNear();
    float getFar();

    float getAlpha();
    float getBeta();
    float getRaio();
};

#endif