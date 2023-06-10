#include "../include/Model.hpp"

Model::Model() {}

Model::Model(vector<Transformation> transformations)
{
    
    this->Transforms = transformations;
}

vector<Point> Model::getPoints()
{
    return this->points;
}

vector<Transformation> Model::getTransformations()
{
    return this->Transforms;
}



vector<float> Model::getVBO()
{
    Point p;
    vector<float> res;

    for (int i = 0; unsigned(i) < points.size(); i++)
    {
        p = points.at(i);
        res.push_back(p.getx());
        res.push_back(p.gety());
        res.push_back(p.getz());
    }

    return res;
}

vector<float> Model::getNormals()
{
    Point v;
    vector<float> res;

    for (int i = 0; unsigned(i) < normals.size(); i++)
    {
        v = normals.at(i);
        res.push_back(v.getx());
        res.push_back(v.gety());
        res.push_back(v.getz());
    }

    return res;
}

vector<float> Model::getTextureCoords()
{
    Point v;
    vector<float> res;

    for (int i = 0; unsigned(i) < textures.size(); i++)
    {
        v = textures.at(i);
        res.push_back(v.getx());
        res.push_back(v.gety());
    }

    return res;
}

void Model::draw(float fps)
{
    
    if(texture == 0){
        glColor3f(diffuse[0], diffuse[1], diffuse[2]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    
        glColor3f(ambient[0], ambient[1], ambient[2]);
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    
        glColor3f(specular[0], specular[1], specular[2]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    
        glColor3f(emissive[0], emissive[1], emissive[2]);
        glMaterialfv(GL_FRONT, GL_EMISSION, emissive);
    
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();


    for (int i = 0; unsigned(i) < Transforms.size(); i++)
    {
        Transforms.at(i).apply(fps);
    }

    
    
    //DrawModel();
    glDrawArrays(GL_TRIANGLES, 0, points_size);
    

    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::DrawModel()
{
    
    Point p,p2,p3;
    float x, x2,x3, y, y2, y3, z, z2, z3;
     
    //glBegin(GL_TRIANGLES);
    //glVertex3f(-1, -1, 1);
    //glVertex3f( -0.333333, -1, 0.333333); 
    //glVertex3f(-0.333333, -1, 1);
    for (int i = 0; unsigned(i) < points.size(); i+=3)
    {
        p = points.at(i);
        x = p.getx();
        y = p.gety();
        z = p.getz();

        p2 = points.at(i+1);
        x2 = p2.getx();
        y2 = p2.gety();
        z2 = p2.getz();
        
        p3 = points.at(i+2);
        x3 = p3.getx();
        y3 = p3.gety();
        z3 = p3.getz();

        //glBegin(GL_TRIANGLES);
        glVertex3f(x, z, y);
        glVertex3f(x2, z2, y2);
        glVertex3f(x3, z3, y3);

        //glEnd();
    }
    glEnd();
}


void Model::setTexture(GLuint texID)
{
    this->texture = texID;
}

GLuint Model::getTexture()
{
    return this->texture;
}

void Model::setDiffuse(float r, float g, float b)
{
    diffuse[0] = r;
    diffuse[1] = g;
    diffuse[2] = b;
    diffuse[3] = 1.0;
}

void Model::setAmbient(float r, float g, float b)
{
    ambient[0] = r;
    ambient[1] = g;
    ambient[2] = b;
    ambient[3] = 1.0;
}

void Model::setSpecular(float r, float g, float b)
{
    specular[0] = r;
    specular[1] = g;
    specular[2] = b;
    specular[3] = 1.0;
}

void Model::setEmissive(float r, float g, float b)
{
    emissive[0] = r;
    emissive[1] = g;
    emissive[2] = b;
    emissive[3] = 1.0;
}

void Model::setShininess(float value)
{
    shininess = value;
}

void Model::freeMem()
{
    points.erase(points.begin(), points.end());
    normals.erase(normals.begin(), normals.end());
    textures.erase(textures.begin(), textures.end());
}

void Model::setPointsSize(int num)
{
    points_size = num;
}

void Model::ReadFile(string shape)
{
    string path = "../generator/GeneratedFiles/";
    path = path + shape;
    ifstream MyFile(path);

    if (!MyFile)
        cout << "File not created!\n" << shape;
    else
    {
        string line{};            // line with 1 triangle
        string value;             // the thing we wanna store
        string delimiter = "|";   // delimiter between x , y , z
        string delimiter2 = "\n";  // delimiter between points
        int pos;                  // position before the delimiter
        float xx, yy, zz;         // Coordenates
        Point p1;         // Points of the readen points

        // Triangulos
        getline(MyFile, line);
        while (0 != strcmp("Normals", line.c_str()))
        {
            //cout << "line : " << line << "\n";
            // Point 1 of the triangle
            pos = line.find(delimiter);
            value = line.substr(0, pos);
            xx = stof(value);
            line.erase(0, pos + delimiter.length()); // erases x + "|"  of the line

            pos = line.find(delimiter);
            value = line.substr(0, pos);
            yy = stof(value);
            line.erase(0, pos + delimiter.length()); // erases y + "|"  of the line
            pos = line.find(delimiter);
            value = line.substr(0, pos);
            zz = stof(value);
            line.erase(0, pos + delimiter2.length()); // erases z + "\n"  of the line
            
            //cout << "x : " << xx << "y : " << yy << "z : " << zz << "\n";

            p1 = Point(xx, yy, zz);

            
            this->points.push_back(p1);
            // creating the triangle and saving it on the globale vector allpoints
            // t = Triangle(p1, p2, p3);
            // points.push_back(t);
            getline(MyFile, line);
        }

        // Normals
        //e = "Normals\n".length();
        getline(MyFile, line);
        while (0 != strcmp("Textures", line.c_str()))
        {
            // Point 1 of the normal
            pos = line.find(delimiter);
            value = line.substr(0, pos);
            xx = atof(value.c_str());
            line.erase(0, pos + delimiter.length()); // erases x + "|"  of the line

            pos = line.find(delimiter);
            value = line.substr(0, pos);
            yy = atof(value.c_str());
            line.erase(0, pos + delimiter.length()); // erases y + "|"  of the line
            pos = line.find(delimiter);
            value = line.substr(0, pos);
            zz = atof(value.c_str());
            line.erase(0, pos + delimiter2.length()); // erases z + "\n"  of the line

            p1 = Point(xx, yy, zz);

            this->normals.push_back(p1);

            getline(MyFile, line);
        }

        // Textures
        //e = "Textures\n".length()

        while (getline(MyFile, line))
        {
            // Point 1 of the texture
            pos = line.find(delimiter);
            value = line.substr(0, pos);
            xx = atof(value.c_str());
            line.erase(0, pos + delimiter.length()); // erases x + "|"  of the line

            pos = line.find(delimiter);
            value = line.substr(0, pos);
            yy = atof(value.c_str());
            line.erase(0, pos + delimiter.length()); // erases y + "|"  of the line
            pos = line.find(delimiter2);
            value = line.substr(0, pos);
            zz = atof(value.c_str());
            line.erase(0, pos + delimiter2.length()); // erases z + "\n"  of the line

            p1 = Point(xx, yy, zz);

            this->textures.push_back(p1);
        }
        MyFile.close();
    }
}