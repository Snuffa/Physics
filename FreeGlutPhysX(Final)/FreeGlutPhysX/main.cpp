//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// Copyright (c) 2013 Media Design School
//
// Author:	Scott Emery
// Grumpy Birds Project
//


#include <iostream>

#include <stdlib.h>
#include <GL/glut.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include <GL\freeglut.h>
#include <math.h>
#include "Game.h"

//#include "vld.h"

using namespace std;

static void Draw();
static void Keyboard(unsigned char _ucChar, int _iX, int _iY);
static void Mouse(int, int, int , int);
static void OnExit();


unsigned int g_uiTimePeriod = 32;

int MainWindow;


// Author: Scott Emery
// Function: Essentially the delta tick. 
// Params: Value - This will be 1 / 60
void static Timer(int value)
{
	glutSetWindow(MainWindow);
	glutPostRedisplay();
	glutTimerFunc(g_uiTimePeriod, Timer, 0);
}


// Author: Scott Emery
// Function: Handles window resizing
// Params: x, y are the positions
void static Resize(int x, int y)
{
	glViewport(0, 0, x, y);
}
void renderBitmapString(float _X, float _Y, float _Z, void* _pfont, char* _pcString);

int main(int argc, char** argv)
{

	// Init window
	glutInit(&argc, argv);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	MainWindow = glutCreateWindow("PhysX");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45,
				   1.333f,
				   1.0f,
				   1000.0f);
	
//	atexit(OnExit);

	//Lighting
	const GLfloat xSpecular[]      = {1.0f, 1.0f, 1.0f, 1.0f};
	const GLfloat xShininess[]     = {50.0f};
	const GLfloat xDiffuse[]       = {1.0f, 1.0f, 1.0f, 1.0f};
	const GLfloat xLightAmbient[]  = {0.1f, 0.1f, 0.1f, 1.0f};
	const GLfloat xLightPosition[] = {10.0f, 10.0f, 10.0f, 0.0f};	

	glShadeModel (GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, xSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, xShininess);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,xDiffuse);

	glLightfv(GL_LIGHT0, GL_AMBIENT, xLightAmbient);
	glLightfv(GL_LIGHT0, GL_POSITION, xLightPosition);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	// Init Process
	CGame::GetInstance().Initialise();

	// register callbacks
	glutDisplayFunc(Draw);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutTimerFunc(g_uiTimePeriod, Timer, 0);
	glutReshapeFunc(Resize);


	// enter Glut event processing cycle
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutMainLoop();

	OnExit();

	return (0);
}

void Draw()
{
	CGame::GetInstance().RenderScene();
	glutPostRedisplay();
}
void Keyboard(unsigned char _ucChar, int _iX, int _iY)
{
	CGame::GetInstance().Keys(_ucChar, _iX, _iY);

}
static void Mouse(int _MouseButton, int _MouseBUpOrDown, int _X, int _Y)
{
	CGame::GetInstance().Mouse(_MouseButton, _MouseBUpOrDown, _X, _Y);
}
void OnExit()
{
	CGame::ShutDown();
}