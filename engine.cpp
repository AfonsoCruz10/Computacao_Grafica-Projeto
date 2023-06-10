#define _USE_MATH_DEFINES
#include <cstdint>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "engine/include/Reader.hpp"

#define FPS 60

using namespace tinyxml2;

using namespace std;

string xmlFile = "../test/test_files_phase_1/test_1_1.xml";

// Frame and time
float timestamp = 0.0f;
int timebase = 0, frame = 0;
float savedMod, timeMod = 0.0001f;
bool isPaused = false;
float speed = 0.1;

#define _PI_ 3.14159

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult)               \
	if (a_eResult != XML_SUCCESS)               \
	{                                           \
		cout << "Error: " << a_eResult << endl; \
	}
#endif

Reader parser;
Camera cam;

int mode = GL_LINES; 

float radians(float x)
{
	return x * 0.01745329252;
}
void drawAxis() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}

void changeSize(int w, int h)
{
	parser.setWindowsizeX(w);
	parser.setWindowsizeY(h);
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(cam.getFov(), ratio, cam.getNear(), cam.getFar());
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void)
{

	char s[64];
	// clear buffers
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	 gluLookAt(cam.getcamX(), cam.getcamY(), cam.getcamZ(),			   // Camera position
			  0, 0, 0, // Look at point
			  0,1,0);			   // Up vector

	 parser.loadLights();

	 glPolygonMode(GL_FRONT_AND_BACK, mode);
	
	//drawAxis();
	 drawAxis();

	//draw models
	glColor3f(1.0f, 1.0f, 1.0f);
	parser.draw();

	frame++;
	int timet = glutGet(GLUT_ELAPSED_TIME);
	if (timet - timebase > 1000) {
		float fps = frame * 1000.0 / (timet - timebase);
		timebase = timet;
		frame = 0;
		sprintf(s, "FPS: %f6.2", fps);
		glutSetWindowTitle(s);
	}
	timestamp += timeMod;

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char key, int xx, int yy)
{
	switch (key)
	{
	case '1':
		mode = GL_LINE;
		break;
	case '2':
		mode = GL_POINT;
		break;
	case '3':
		mode = GL_FILL;
		break;
	case '+':
		cam.setRaio(cam.getRaio() - 50.0f);
		if (cam.getRaio() < 1.0f)
			cam.setRaio(10.0f);
		break;
	case '-':
		cam.setRaio(cam.getRaio() + 100.0f);
		break;
	case 'w':
		cam.setBeta(cam.getBeta() + 0.1f);
		if (cam.getBeta() > 1.5f)
			cam.setBeta(1.5f);
		break;
	case 's':
		cam.setBeta(cam.getBeta() - 0.1f);
		if (cam.getBeta() < -1.5f)
			cam.setBeta(-1.5f);
		break;
	case 'a':
		cam.setAlpha(cam.getAlpha() - 0.1f);
		break;
		break;
	case 'd':
		cam.setAlpha(cam.getAlpha() + 0.1f);
		break;
		break;
	case 'r':
		cam.setAlpha(0.75f);
		cam.setBeta(0.5f);
		cam.setRaio(200.0f);
		cam.centerX = 0.0f;
		cam.centerY = 0.0f;
		cam.centerZ = 0.0f;
		timestamp = 0.0f;
		timeMod = 0.0001f;
		//mode = GL_FILL;
		break;
	case 'p':
			if (!isPaused)
			{
				isPaused = true;
				savedMod = timeMod;
				timeMod = 0.0f;
			}
			else
			{
				isPaused = false;
				timeMod = savedMod;
			}
			break;
	case 'i':
			 timeMod *= 100;
			break;
	case 'o':
			timeMod /= 50;
			break;
	}
	cam.spherical2Cartesian();
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy)
{

	switch (key)
	{

	case GLUT_KEY_RIGHT:
		cam.centerX += 0.5f;
		break;

	case GLUT_KEY_LEFT:
		cam.centerX -= 0.5f;
		break;

	case GLUT_KEY_UP:
		cam.centerZ -= 0.5f;
		break;

	case GLUT_KEY_DOWN:
		cam.centerZ += 0.5f;
		break;
	}
	cam.spherical2Cartesian();
	glutPostRedisplay();
}

void passive_motion(int x, int y)
{
	int dev_x, dev_y;

	dev_x = (parser.getWindowsizeX() / 2) - x;
	dev_y = (parser.getWindowsizeY() / 2) - y;

	cam.setAlpha(cam.getAlpha() + speed * (float)dev_x);
	cam.setBeta(cam.getBeta() + speed * (float)dev_y);
}

void timer(int)
{
	glutPostRedisplay();
	//glutWarpPointer(parser.getWindowsizeX() / 2, parser.getWindowsizeY() / 2);
	glutTimerFunc(1000 / FPS, timer, 0);
}

void init()
{
	//glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPolygonMode(GL_FRONT, mode);
	glEnable(GL_LIGHTING);
	glEnable(GL_RESCALE_NORMAL);
	glEnable(GL_TEXTURE_2D);

	float amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	for (int i = 0; i < parser.getLightNum(); i++)
	{
		glEnable(GL_LIGHT0 + i);
	}

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	parser.initGroupParser(xmlFile);

	//glutWarpPointer(parser.getWindowsizeX() / 2, parser.getWindowsizeY() / 2);
}

int main(int argc, char **argv)
{
	parser.readxml(xmlFile);
	cam = parser.getCamera();


	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(parser.getWindowsizeX(), parser.getWindowsizeY());
	glutCreateWindow("Solar");

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	ilInit();

	// Required callback registry
	init();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	//glutPassiveMotionFunc(passive_motion);
	glutTimerFunc(0, timer, 0);
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	//glutIdleFunc(renderScene);

	// enter GLUT's main cycle
	glutMainLoop();
	return 1;
}