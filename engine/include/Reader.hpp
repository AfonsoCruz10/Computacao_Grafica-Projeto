#ifndef READER_HPP
#define READER_HPP

#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "../../generator/include/Shape.hpp"
#include "../../generator/include/Point.hpp"
#include "Tinyxml2.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include <IL/il.h>
#include <map>
#include "Light.hpp"

using namespace tinyxml2;

using namespace std;

class Reader
{
private:
    int windowsizex;
    int windowsizey;
    Camera cam;
    vector<Model> Models;
    char *filemodel;

    vector<Light> lights;
    vector<int> indices;

    int models_num = 0;

    GLuint *buffers = nullptr;
    GLuint *normal_buffers = nullptr;
    GLuint *texture_buffers = nullptr;

    map<char *, GLuint> textures;

    float fps = 60.0;

public:
    Reader();

    void Reader::readxml(string);
    void Reader::initGroupParser(string path);
    void Reader::groupParser(XMLNode *, vector<Transformation>);

    float Reader::getWindowsizeX();
    float Reader::getWindowsizeY();
    Camera Reader::getCamera();
    int Reader::getLightNum();
    vector<Model> Reader::getModels();

    void Reader::setCamera(Camera);
    void Reader::setFPS(float);
    void Reader::draw();
    void Reader::setBuffers(GLuint *);
    GLuint Reader::loadTexture(char *);
    void Reader::loadLights();
    void setWindowsizeX(int);
    void setWindowsizeY(int);
};

#endif