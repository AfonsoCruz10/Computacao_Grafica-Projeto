#include "../include/Bezier.hpp"
#include "../include/Point.hpp"
#include "../include/Shape.hpp"

using namespace std;

void Bezier::parseBezier(const char *inputFile)
{
    // ----------------------------------------------------------
    // Parse input file
    // ----------------------------------------------------------

    vector<Point> bezierPoints;
    ifstream file(inputFile);
    string line;
    int patches_nr = 0, points_nr = 0;

    if (file.fail())
    {
        cout << "Couldn't find file: " << inputFile << endl;
    }

    // Number of patches
    getline(file, line);
    patches_nr = stoi(line);
    vector<vector<int>> patch_index(patches_nr, vector<int>(16));

    for (int i = 0; i < patches_nr; i++)
    {
        getline(file, line);

        for (int j = 0; j < 16; j++)
        {
            int split = line.find(",");
            string s = line.substr(0, split);
            patch_index[i][j] = stoi(s);
            line.erase(0, split + 1);
        }
    }

    // Number of points
    getline(file, line);
    points_nr = stoi(line);
    int cr[3];

    for (int i = 0; i < points_nr; i++)
    {
        getline(file, line);
        for (int j = 0; j < 3; j++)
        {
            int split = line.find(",");
            string s = line.substr(0, split);
            cr[j] = stof(s);
            line.erase(0, split + 1);
        }

        bezierPoints.push_back(Point(cr[0], cr[1], cr[2]));
    }

    for (int i = 0; i < patches_nr; i++)
    {
        Shape s;

        for (int j = 0; j < 16; j++)
        {
            Point auxPoint = bezierPoints.at(patch_index[i][j]);
            s.addPoint(auxPoint);
        }

        patches.push_back(s);
    }
}

void Bezier::bezierPoints(int tessellation)
{
    float divisions = 1.0 / tessellation, u, u2, v, v2;

    for (int i = 0; i < patches.size(); i++)
    {
        Shape s = patches.at(i);

        for (int vs = 0; vs < tessellation; vs++)
        {
            for (int us = 0; us < tessellation; us++)
            {
                u = us * divisions;
                u2 = (us + 1) * divisions;
                v = vs * divisions;
                v2 = (vs + 1) * divisions;

                Point p1 = bezierPatch(u, v, s);
                Point p2 = bezierPatch(u2, v, s);
                Point p3 = bezierPatch(u, v2, s);
                Point p4 = bezierPatch(u2, v2, s);

                this->addPoint(p1);
                this->addNormal(p1.normalizeB(p3, p4));
                this->addTextureP(Point(u2, v));

                this->addPoint(p2);
                this->addNormal(p1.normalizeB(p4, p2));
                this->addTextureP(Point(u, v));

                this->addPoint(p4);
                this->addNormal(p4.normalizeB(p2, p1));
                this->addTextureP(Point(u2, v2));

                this->addPoint(p1);
                this->addNormal(p1.normalizeB(p3, p4));
                this->addTextureP(Point(u, v));

                this->addPoint(p4);
                this->addNormal(p3.normalizeB(p4, p1));
                this->addTextureP(Point(u, v2));

                this->addPoint(p3);
                this->addNormal(p4.normalizeB(p1, p3));
                this->addTextureP(Point(u2, v2));
            }
        }
    }
}

Point Bezier::bezierPatch(float u, float v, Shape patch)
{
    Point pts_u[4];
    Point pts_v[4];

    int j = 0, k = 0;

    for (int i = 0; i < 16; i++)
    {
        Point aux = patch.getPoint(i);
        pts_u[j] = aux;
        j++;

        if (j == 4)
        {
            pts_v[k++] = bValue(u, pts_u[0], pts_u[1], pts_u[2], pts_u[3]);

            j = 0;
        }
    }

    Point res = bValue(v, pts_v[0], pts_v[1], pts_v[2], pts_v[3]);

    return res;
}

Point Bezier::bValue(float u, Point p0, Point p1, Point p2, Point p3)
{
    float b0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
    float b1 = 3.0 * u * (1.0 - u) * (1.0 - u);
    float b2 = 3 * u * u * (1.0 - u);
    float b3 = u * u * u;

    float x = p0.getx() * b0 + p1.getx() * b1 + p2.getx() * b2 + p3.getx() * b3;
    float y = p0.gety() * b0 + p1.gety() * b1 + p2.gety() * b2 + p3.gety() * b3;
    float z = p0.getz() * b0 + p1.getz() * b1 + p2.getz() * b2 + p3.getz() * b3;

    return Point(x, y, z);
}