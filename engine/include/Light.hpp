#ifndef LIGHT_HPP
#define LIGHT_HPP

using namespace std;

class Light
{
private:
    int type; // 0 - Point | 1 - Directional | 2 - Spotlight

    float pos[4];
    float dir[3];

    float cutoff;

public:
    Light();

    void setPos(float x, float y, float z, float dirOrPoint);
    void setDir(float x, float y, float z);
    void setCutoff(float value);
    void setType(int value);

    int getType();
    float *getPos();
    float *getDir();
    float getCutoff();
};

#endif