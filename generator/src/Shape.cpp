#include "../include/Shape.hpp"
#include <cmath>

Shape::Shape()
{
}

Shape::Shape(vector<Point> pointsp)
{
    this->points = pointsp;
}

void Shape::addPoint(Point toAdd)
{
    points.push_back(toAdd);
}

void Shape::addNormal(Point normal)
{
    normals.push_back(normal);
}

void Shape::addTextureP(Point texture)
{
    textures.push_back(texture);
}

void Shape::serialize(string filename)
{
    char buff[1024];
    Point v;

    ofstream file(filename, ofstream::out);

    //sprintf(buff, "%d\n", points.size());
    //file << buff;

    for (int i = 0; i < points.size(); i++)
    {
        v = points.at(i);

        sprintf(buff, "%f|%f|%f\n", v.getx(), v.gety(), v.getz());
        file << buff;
    }

    sprintf(buff, "Normals\n", normals.size());
    file << buff;

    for (int i = 0; i < normals.size(); i++)
    {
        v = normals.at(i);

        sprintf(buff, "%f|%f|%f\n", v.getx(), v.gety(), v.getz());
        file << buff;
    }

    sprintf(buff, "Textures\n", textures.size());
    file << buff;

    for (int i = 0; i < textures.size(); i++)
    {
        v = textures.at(i);

        sprintf(buff, "%f|%f\n", v.getx(), v.gety());
        file << buff;
    }

    file.close();
}

Point Shape::getPoint(int indice)
{
    return points.at(indice);
}
vector<Point> Shape::getPoints()
{
    return points;
}

vector<float> Shape::getVBO()
{
    Point v;
    vector<float> res;

    for (int i = 0; i < points.size(); i++)
    {
        v = points.at(i);
        res.push_back(v.getx());
        res.push_back(v.gety());
        res.push_back(v.getz());
    }

    return res;
}