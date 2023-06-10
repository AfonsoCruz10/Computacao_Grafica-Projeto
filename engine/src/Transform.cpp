#include "../include/Transform.hpp"

Transformation::Transformation() {
    this->angle = 0;
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->type = 't';
}

Transformation::Transformation(char t, float x, float y, float z)
{
    this->angle = 0;
    this->x = x;
    this->y = y;
    this->z = z;
    this->type = t;
}

Transformation::Transformation(float angle, float x, float y, float z)
{
    this->angle = angle;
    this->x = x;
    this->y = y;
    this->z = z;
    this->type = 'r';
}

float Transformation::getAngle()
{
    return this->angle;
}

float Transformation::getX()
{
    return this->x;
}

float Transformation::getY()
{
    return this->y;
}

float Transformation::getZ()
{
    return this->z;
}

char Transformation::getType()
{
    return this->type;
}

void Transformation::setTime(float newTime)
{
    this->time = newTime;
}

void Transformation::setID(int x)
{
    id = x;
}

void Transformation::setType(char newType)
{
    type = newType;
}

void Transformation::setAlign(bool newAlign)
{
    align = newAlign;
}

void Transformation::addPoint(Point toAdd)
{
    points.push_back(toAdd);
}

void Transformation::apply(float fps)
{
    if (type == 't')
    {
        if (id == 0)
        {
            glTranslatef(x, y, z);
        }
        else if (drawCurves)
        {
            glBegin(GL_LINE_LOOP);
            for (int i = 0; i < 100; i++)
            {
                float gt = (float)i / 100.0;

                float pos[3];
                float deriv[3];

                getGlobalCatmullRomPoint(gt, pos, deriv);

                glVertex3f(pos[0], pos[1], pos[2]);
            }

            glEnd();

            float pos[3];
            float deriv[3];

            getGlobalCatmullRomPoint(tg, pos, deriv);

            glTranslatef(pos[0], pos[1], pos[2]);

            if (align)
            {
                float z[3];

                cross(deriv, yt, z);
                cross(z, deriv, yt);

                normalize(deriv);
                normalize(yt);
                normalize(z);

                float m[16];
                buildRotMatrix(deriv, yt, z, m);

                glMultMatrixf(m);
            }

            tg += 1 / (time * fps);
        }
    }
    else if (type == 'r')
    {
        if (id == 0)
        {
            glRotatef(angle, x, y, z);
        }
        else
        {
            angle += 360.0 / (time * fps);

            glRotatef(angle, x, y, z);
        }
    }
    else
    {
        glScalef(x, y, z);
    }
}

void Transformation::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv)
{
    float t = gt * points.size();
    int index = floor(t);

    t = t - index;

    int indices[4] = { 0,0,0,0 };
    indices[0] = (index + points.size() - 1) % points.size();
    indices[1] = (indices[0] + 1) % points.size();
    indices[2] = (indices[1] + 1) % points.size();
    indices[3] = (indices[2] + 1) % points.size();

    getCatmullRomPoint(t, points[indices[0]], points[indices[1]], points[indices[2]], points[indices[3]], pos, deriv);
}

void Transformation::getCatmullRomPoint(float t, Point p0, Point p1, Point p2, Point p3, float *pos, float *deriv)
{
    float m[4][4] = {{-0.5f, 1.5f, -1.5f, 0.5f},
                     {1.0f, -2.5f, 2.0f, -0.5f},
                     {-0.5f, 0.0f, 0.5f, 0.0f},
                     {0.0f, 1.0f, 0.0f, 0.0f}};

    float tm[4] = {powf(t, 3.0), powf(t, 2.0), t, 1.0};
    float tmd[4] = {powf(t, 2.0), t, 1.0, 0.0};

    for (int i = 0; i < 3; i++)
    {
        float P[4] = { 0,0,0,0 };

        if (i == 0)
        {
            P[0] = p0.getx();
            P[1] = p1.getx();
            P[2] = p2.getx();
            P[3] = p3.getx();
        }
        else if (i == 1)
        {
            P[0] = p0.gety();
            P[1] = p1.gety();
            P[2] = p2.gety();
            P[3] = p3.gety();
        }
        else
        {
            P[0] = p0.getz();
            P[1] = p1.getz();
            P[2] = p2.getz();
            P[3] = p3.getz();
        }

        float a[4];
        multMatrixVector((float *)m, P, a);

        pos[i] = 0.0;
        deriv[i] = 0.0;

        for (int j = 0; j < 4; j++)
        {
            pos[i] += tm[j] * a[j];
            deriv[i] += tmd[j] * a[j];
        }
    }
}

void Transformation::multMatrixVector(float *m, float *v, float *res)
{
    for (int j = 0; j < 4; ++j)
    {
        res[j] = 0;
        for (int k = 0; k < 4; ++k)
        {
            res[j] += v[k] * m[j * 4 + k];
        }
    }
}

void Transformation::cross(float *a, float *b, float *res)
{

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

void Transformation::normalize(float *a)
{
    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

void Transformation::buildRotMatrix(float *x, float *y, float *z, float *m)
{
    m[0] = x[0];
    m[1] = x[1];
    m[2] = x[2];
    m[3] = 0;
    m[4] = y[0];
    m[5] = y[1];
    m[6] = y[2];
    m[7] = 0;
    m[8] = z[0];
    m[9] = z[1];
    m[10] = z[2];
    m[11] = 0;
    m[12] = 0;
    m[13] = 0;
    m[14] = 0;
    m[15] = 1;
}
