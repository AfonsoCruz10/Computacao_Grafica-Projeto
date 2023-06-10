
#include "../include/Reader.hpp"

using namespace std;

using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult)               \
    if (a_eResult != XML_SUCCESS)               \
    {                                           \
        cout << "Error: " << a_eResult << endl; \
    }
#endif

Reader::Reader()
{
    windowsizex = 800;
    windowsizey = 800;
    cam = Camera();
    Models = vector<Model>();
}

void Reader::initGroupParser(string path) {
    
    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile(path.c_str());
    XMLCheckResult(eResult);
    XMLNode* pRoot = xmlDoc.FirstChild();
    if (pRoot == nullptr) cout << "XML file not found\n";
    if (pRoot != nullptr)
    {
        XMLElement* pGroup = pRoot->FirstChildElement("group");
        for (; NULL != pGroup; pGroup = pGroup->NextSiblingElement("group"))
        {
            groupParser(pGroup, vector<Transformation>());

        }
    }
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Reader::groupParser(XMLNode *pGroup, vector<Transformation> TransVec)
{
    
    string filename;
    float x, y, z;
    float time = -1;
    float rotateAngle;
    Transformation AuxTransform = Transformation();
    Model AuxModel;

    if (pGroup != NULL)
    {
        XMLElement *pTransform = pGroup->FirstChildElement("transform");
        if (NULL != pTransform)
        {
            XMLElement *transform;
            for (transform = pTransform->FirstChildElement(); transform != NULL; transform = transform->NextSiblingElement())
            {
                if (strcmp(transform->Name(), "rotate") == 0)
                {
                    if (strcmp(transform->FirstAttribute()->Name(), "time") == 0)
                    {
                        
                        transform->QueryFloatAttribute("time", &time);
                        if (time < 0)
                            time = 0;
                    }
                    else
                    {
                        transform->QueryFloatAttribute("angle", &rotateAngle);
                    }
                    transform->QueryFloatAttribute("x", &x);
                    transform->QueryFloatAttribute("y", &y);
                    transform->QueryFloatAttribute("z", &z);
                    if (time >= 0)
                    {
                        AuxTransform = Transformation('r', x, y, z);
                        AuxTransform.setID(1);
                        AuxTransform.setTime(time);
                    }
                    else
                        AuxTransform = Transformation(rotateAngle, x, y, z);
                    TransVec.push_back(AuxTransform);
                }

                if (strcmp(transform->Name(), "translate") == 0)
                {
                    if (strcmp(transform->FirstAttribute()->Name(), "time") == 0)
                    {
                        AuxTransform.setID(1);
                        AuxTransform.setType('t');
                        float time;
                        transform->QueryFloatAttribute("time", &time);
                        AuxTransform.setTime(time);

                        const char *auxAlign = transform->Attribute("align");
                        if (strcmp(auxAlign, "true") == 0)
                        {
                            AuxTransform.setAlign(true);
                        }

                        XMLElement *point = transform->FirstChildElement("point");
                        while (point != NULL)
                        {
                            float x;
                            point->QueryFloatAttribute("x", &x);

                            float y;
                            point->QueryFloatAttribute("y", &y);

                            float z;
                            point->QueryFloatAttribute("z", &z);

                            AuxTransform.addPoint(Point(x, y, z));

                            point = point->NextSiblingElement();
                        }
                        TransVec.push_back(AuxTransform);
                    }
                    else
                    {
                        transform->QueryFloatAttribute("x", &x);
                        transform->QueryFloatAttribute("y", &y);
                        transform->QueryFloatAttribute("z", &z);
                        AuxTransform = Transformation('t', x, y, z);
                        TransVec.push_back(AuxTransform);
                    }
                }

                if (strcmp(transform->Name(), "scale") == 0)
                {
                    transform->QueryFloatAttribute("x", &x);
                    transform->QueryFloatAttribute("y", &y);
                    transform->QueryFloatAttribute("z", &z);
                    AuxTransform = Transformation('s', x, y, z);
                    TransVec.push_back(AuxTransform);
                }
            }
        }

        XMLElement *pmodels = pGroup->FirstChildElement("models");
        if (NULL != pmodels)
        {
            XMLElement *pmodel;
            for (pmodel = pmodels->FirstChildElement("model"); pmodel != NULL; pmodel = pmodel->NextSiblingElement("model"))
            {
                AuxModel = Model(TransVec);
                filename = pmodel->Attribute("file");
                AuxModel.ReadFile(filename);

                XMLElement *texture = pmodel->FirstChildElement("texture");

                if (texture != NULL)
                {
                    string aux_texture = texture->Attribute("file");
                    aux_texture = "../textures/" + aux_texture;
                    char *texture_file = &aux_texture[0];
                    cout << texture_file << "\n";
                    GLuint texID;

                    if (1)//textures.find(texture_file) == textures.end())
                    {
                        texID = loadTexture(texture_file);

                        textures.insert(pair<char *, GLuint>(texture_file, texID));
                    }
                    else
                    {
                        texID = textures.find(texture_file)->second;
                    }

                    AuxModel.setTexture(texID);
                }

                XMLElement *color = pmodel->FirstChildElement("color");

                if (color != NULL)
                {
                    float r, g, b, value;

                    XMLElement* diffuse = color->FirstChildElement("diffuse");
                    if (diffuse != NULL) {
                        diffuse->QueryFloatAttribute("R", &r);
                        diffuse->QueryFloatAttribute("G", &g);
                        diffuse->QueryFloatAttribute("B", &b);

                        AuxModel.setDiffuse(r / 255.0, g / 255.0, b / 255.0);
                    }
                    XMLElement* ambient = color->FirstChildElement("ambient");
                    if (ambient != NULL) {
                        ambient->QueryFloatAttribute("R", &r);
                        ambient->QueryFloatAttribute("G", &g);
                        ambient->QueryFloatAttribute("B", &b);

                        AuxModel.setAmbient(r / 255.0, g / 255.0, b / 255.0);
                    }
                    XMLElement* specular = color->FirstChildElement("specular");
                    if (specular != NULL) {
                        specular->QueryFloatAttribute("R", &r);
                        specular->QueryFloatAttribute("G", &g);
                        specular->QueryFloatAttribute("B", &b);

                        AuxModel.setSpecular(r / 255.0, g / 255.0, b / 255.0);
                    }
                    XMLElement* emissive = color->FirstChildElement("emissive");
                    if (emissive != NULL) {
                        emissive->QueryFloatAttribute("R", &r);
                        emissive->QueryFloatAttribute("G", &g);
                        emissive->QueryFloatAttribute("B", &b);

                        AuxModel.setEmissive(r / 255.0, g / 255.0, b / 255.0);
                    }
                    XMLElement* shininess = color->FirstChildElement("shininess");
                    if (shininess != NULL) {
                        shininess->QueryFloatAttribute("value", &value);

                        AuxModel.setShininess(value);
                    }
                }

                const size_t lastIndex = Models.size();

                if (buffers == nullptr) {
                    buffers = (GLuint*)malloc( sizeof(GLuint) * (lastIndex + 1));
                    normal_buffers = (GLuint*)malloc( sizeof(GLuint) * (lastIndex + 1));
                    texture_buffers = (GLuint*)malloc( sizeof(GLuint) * (lastIndex + 1));
                }
                else {
                    buffers = (GLuint*)realloc(buffers, sizeof(GLuint) * (lastIndex + 1));
                    normal_buffers = (GLuint*)realloc(normal_buffers, sizeof(GLuint) * (lastIndex + 1));
                    texture_buffers = (GLuint*)realloc(texture_buffers, sizeof(GLuint) * (lastIndex + 1));
                }
                


                glGenBuffers(1, &buffers[lastIndex]);//Models.size()
                glBindBuffer(GL_ARRAY_BUFFER, buffers[lastIndex]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * AuxModel.getVBO().size(), AuxModel.getVBO().data(), GL_STATIC_DRAW);
                
                glGenBuffers(1, &normal_buffers[lastIndex]);
                glBindBuffer(GL_ARRAY_BUFFER, normal_buffers[lastIndex]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * AuxModel.getNormals().size(), AuxModel.getNormals().data(), GL_STATIC_DRAW);
                
                glGenBuffers(1, &texture_buffers[lastIndex]);
                glBindBuffer(GL_ARRAY_BUFFER, texture_buffers[lastIndex]);
                glBufferData(GL_ARRAY_BUFFER, sizeof(float) * AuxModel.getTextureCoords().size(), AuxModel.getTextureCoords().data(), GL_STATIC_DRAW);
                
                //cout << &buffers[lastIndex] << "\n";

                AuxModel.setPointsSize(AuxModel.getPoints().size());  
                //AuxModel.freeMem();

                this->Models.push_back(AuxModel);

            }
        }
    }
    XMLElement *group = pGroup->FirstChildElement("group");
    for(; NULL != group; group = group->NextSiblingElement("group"))
    {
        groupParser(group, TransVec);

    }
}



void Reader::readxml(string path)
{
    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile(path.c_str());
    XMLCheckResult(eResult);
    XMLNode *pRoot = xmlDoc.FirstChild();
    float x, y, z;
    if (pRoot == nullptr) cout << "XML file not found\n";
    if (pRoot != nullptr)
    {
        // Window settings
        XMLElement *window = pRoot->FirstChildElement("window");
        if (NULL != window)
        {
            window->QueryIntAttribute("width", &windowsizex);
            window->QueryIntAttribute("height", &windowsizey);
        }

        // Camera settings
        XMLElement *pCam = pRoot->FirstChildElement("camera");
        if (NULL != pCam)
        {

            XMLElement *pPos = pCam->FirstChildElement("position");
            if (NULL != pPos)
            {
                pPos->QueryFloatAttribute("x", &x);
                pPos->QueryFloatAttribute("y", &y);
                pPos->QueryFloatAttribute("z", &z);
                cam.setcamX(x);
                cam.setcamY(y);
                cam.setcamZ(z);
            }

            XMLElement *pLookAt = pCam->FirstChildElement("lookAt");
            float xx = 0, yy = 0, zz = 0;
            if (NULL != pLookAt)
            {
                pLookAt->QueryFloatAttribute("x", &x);
                pLookAt->QueryFloatAttribute("y", &y);
                pLookAt->QueryFloatAttribute("z", &z);
                cam.setcamLookX(x);
                cam.setcamLookY(y);
                cam.setcamLookZ(z);
            }

            XMLElement *pUp = pCam->FirstChildElement("up");
            if (NULL != pUp)
            {
                pUp->QueryFloatAttribute("x", &x);
                pUp->QueryFloatAttribute("y", &y);
                pUp->QueryFloatAttribute("z", &z);
                cam.setUPx(x);
                cam.setUPy(y);
                cam.setUPz(z);
            }
            XMLElement *pProjection = pCam->FirstChildElement("projection");
            if (NULL != pProjection)
            {
                pProjection->QueryFloatAttribute("fov", &x);
                pProjection->QueryFloatAttribute("near", &y);
                pProjection->QueryFloatAttribute("far", &z);
                cam.setFov(x);
                cam.setNear(y);
                cam.setFar(z);
            }
        }

        XMLElement* lightsE = pRoot->FirstChildElement("lights");

        if (lightsE != NULL)
        {
            XMLElement* light;

            for (light = lightsE->FirstChildElement("light"); light != NULL; light = light->NextSiblingElement("light"))
            {
                Light l;
                float x, y, z, cutoff;

                const char* aux_type;
                aux_type = light->Attribute("type");

                if (strcmp(aux_type, "point") == 0)
                {
                    l.setType(0);

                    light->QueryFloatAttribute("posx", &x);
                    light->QueryFloatAttribute("posy", &y);
                    light->QueryFloatAttribute("posz", &z);

                    l.setPos(x, y, z, 1.0);
                }
                else if (strcmp(aux_type, "directional") == 0)
                {
                    l.setType(1);

                    light->QueryFloatAttribute("dirx", &x);
                    light->QueryFloatAttribute("diry", &y);
                    light->QueryFloatAttribute("dirz", &z);

                    l.setPos(x, y, z, 0.0);
                }
                else
                {
                    l.setType(2);

                    light->QueryFloatAttribute("posx", &x);
                    light->QueryFloatAttribute("posy", &y);
                    light->QueryFloatAttribute("posz", &z);

                    l.setPos(x, y, z, 1.0);

                    light->QueryFloatAttribute("dirx", &x);
                    light->QueryFloatAttribute("diry", &y);
                    light->QueryFloatAttribute("dirz", &z);

                    l.setDir(x, y, z);

                    light->QueryFloatAttribute("cutoff", &cutoff);

                    l.setCutoff(cutoff);
                }

                lights.push_back(l);
            }
        }
    }
}

void Reader::draw()
{
    int i;
    for (i = 0; unsigned(i) < Models.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffers[i]);
        glNormalPointer(GL_FLOAT, 0, 0);
        
        glBindBuffer(GL_ARRAY_BUFFER, texture_buffers[i]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        Models.at(i).draw(fps);
    }
}

void Reader::setBuffers(GLuint *b)
{
    buffers = b;
}

float Reader::getWindowsizeX()
{
    return this->windowsizex;
}

float Reader::getWindowsizeY()
{
    return this->windowsizey;
}

Camera Reader::getCamera()
{
    return this->cam;
}

void Reader::setCamera(Camera camx)
{
    cam = camx;
}

vector<Model> Reader::getModels()
{
    return this->Models;
}

void Reader::setFPS(float newFPS)
{
    fps = newFPS;
}

void Reader::loadLights()
{
    int i;
    for (i = 0; unsigned(i) < lights.size(); i++)
    {
        if (lights.at(i).getType() == 0)
        {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lights.at(i).getPos());
        }
        else if (lights.at(i).getType() == 1)
        {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lights.at(i).getPos());
        }
        else
        {
            glLightfv(GL_LIGHT0 + i, GL_POSITION, lights.at(i).getPos());
            glLightfv(GL_LIGHT0 + i, GL_SPOT_DIRECTION, lights.at(i).getDir());
            glLightf(GL_LIGHT0 + i, GL_SPOT_CUTOFF, lights.at(i).getCutoff());
        }
    }
}

void Reader::setWindowsizeX(int x)
{
    this->windowsizex = x;
}
void Reader::setWindowsizeY(int x)
{
    this->windowsizey = x;
}

int Reader::getLightNum()
{
    return this->lights.size();
}

GLuint Reader::loadTexture(char *s) {

    unsigned int t, tw, th;
    unsigned char* texData;
    unsigned int texID;

    ilGenImages(1, &t);
    ilBindImage(t);
    if(ilLoadImage((ILstring)s)) cout << "nice\n";
    else cout << "sad\n";
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);

    texData = ilGetData();

    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

}
