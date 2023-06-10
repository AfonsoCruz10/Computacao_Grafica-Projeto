#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>
#include <string>
#include "../include/Transform.hpp"
#include "../../generator/include/Shape.hpp"
#include "../../generator/include/Point.hpp"

class Model
{
private:
    vector<Transformation> Transforms;
    vector<Point> points;
    vector<Point> normals;
    vector<Point> textures;

    int points_size = 0;

    float ambient[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float diffuse[4] = { 1.0f, 1.0f, 1, 1.0f };
    float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float emissive[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
    float shininess = 0;

    GLuint texture = 0;

public:
    Model();
    Model(vector<Transformation>);
    void Model::ReadFile(string);

    void executeTransformations(float);
    void draw(float);
    void Model::DrawModel();

    GLuint getTexture();
    vector<Transformation> getTransformations();
    vector<Point> getPoints();
    vector<float> getVBO();
    vector<float> getNormals();
    vector<float> getTextureCoords();

    void freeMem();
    void setTexture(GLuint);
    void setPointsSize(int);
    void setDiffuse(float, float, float);
    void setAmbient(float, float, float);
    void setSpecular(float, float, float);
    void setEmissive(float, float, float);
    void setShininess(float);
};

#endif