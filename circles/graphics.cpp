// OpenGL/GLUT starter kit for Windows 7 and Visual Studio 2010
// Created spring, 2011
//
// This is a starting point for OpenGl applications.
// Add code to the "display" function below, or otherwise
// modify this file to get your desired results.
//
// For the first assignment, add this file to an empty Windows Console project
//		and then compile and run it as is.
// NOTE: You should also have glut.h,
// glut32.dll, and glut32.lib in the directory of your project.
// OR, see GlutDirectories.txt for a better place to put them.

#include <cmath>
#include <cstring>
#include <string>
#if WIN32
#include "glut.h"
#else // Linux
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>
#endif



// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
double gX = 200;
double gY = 200;
double gDX = .1;
double gDY = .07;

double x1 = rand() % 700;
double x2 = rand() % 700;
double x3 = rand() % 700;
double x4 = rand() % 700;
double x5 = rand() % 700;
double x6 = rand() % 700;
double x7 = rand() % 700;
double x8 = rand() % 700;
double x9 = rand() % 700;
double x10 = rand() % 700;

double y = rand() % 30 + 400;
double y2 = rand() % 30 + 400;
double y3 = rand() % 30 + 400;
double y4 = rand() % 30 + 400;
double y5 = rand() % 30 + 400;
double y6 = rand() % 30 + 400;
double y7 = rand() % 30 + 400;
double y8 = rand() % 30 + 400;
double y9 = rand() % 30 + 400;
double y10 = rand() % 30 + 400;

double dx1 = rand() % 3 + 1;
double dx2 = rand() % 3 + 1;
double dx3 = rand() % 3 + 1;
double dx4 = rand() % 3 + 1;
double dx5 = rand() % 3 + 1;
double dx6 = rand() % 3 + 1;
double dx7 = rand() % 3 + 1;
double dx8 = rand() % 3 + 1;
double dx9 = rand() % 3 + 1;
double dx10 = rand() % 3 + 1;

double dy1 = rand() % 2 + 5;
double dy2 = rand() % 2 + 5;
double dy3 = rand() % 2 + 5;
double dy4 = rand() % 2 + 5;
double dy5 = rand() % 2 + 5;
double dy6 = rand() % 2 + 5;
double dy7 = rand() % 2 + 5;
double dy8 = rand() % 2 + 5;
double dy9 = rand() % 2 + 5;
double dy10 = rand() % 2 + 5;

double r1 = rand() % 20 + 30;
double r2 = rand() % 20 + 30;
double r3 = rand() % 20 + 30;
double r4 = rand() % 20 + 30;
double r5 = rand() % 20 + 30;
double r6 = rand() % 20 + 30;
double r7 = rand() % 20 + 30;
double r8 = rand() % 20 + 30;
double r9 = rand() % 20 + 30;
double r10 = rand() % 20 + 30;

std::vector<double> xVals = {x1, x2, x3, x4, x5, x6, x7, x8, x9, x10};
std::vector<double> yVals = {y, y2, y3, y4, y5, y6, y7, y8, y9, y10};
std::vector<double> dyVals = {dy1, dy2, dy3, dy4, dy5, dy6, dy7, dy8, dy9, dy10};
std::vector<double> dxVals = {dx1, dx2, dx3, dx4, dx5, dx6, dx7, dx8, dx9, dx10};
std::vector<double> rVals = {r1, r2, r3, r4, r5, r6, r7, r8, r9, r10};




// 
// Functions that draw basic primitives
//
void DrawShape(double x1, double y1, double len, int sides)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<sides; i++)
	{
		double theta = 360.0/(sides*i);
		double x = x1 + len * cos(theta);
		double y = y1 + len * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}
void DrawCircle(double x1, double y1, double radius)
{
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3)
{
	glBegin(GL_TRIANGLES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
	glVertex2d(x3,y3);
	glEnd();
}

// Outputs a string of text at the specified location.
void DrawText(double x, double y, const char *string)
{
	void *font = GLUT_BITMAP_9_BY_15;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	
	int len, i;
	glRasterPos2d(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++) 
	{
		glutBitmapCharacter(font, string[i]);
	}

    glDisable(GL_BLEND);
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Test lines that draw all three shapes and some text.
	// Delete these when you get your code working.
	std::vector<std::vector<int>> colors = {
		{0,0,1},
		{1,0,0},
		{0,1,0},
		{0,1,55},
		{55,1,0},
		{10,55,0},
		{0,1,88},
		{1,0,0},
		{0,10,40},
		{0,1,0},
	};

	for(int i=0; i<10; i++){
		glColor3d(colors[i][0], colors[i][1], colors[i][2]);
		DrawCircle(xVals[i], yVals[i], rVals[i]);
	}

	for(int i=0; i<10; i++){
		if (xVals[i] + dxVals[i] + rVals[i] > screen_x || xVals[i] + dxVals[i] - rVals[i] < 0){
			dxVals[i] = -dxVals[i];
		}
		if (yVals[i] + dyVals[i] + rVals[i] > screen_y || yVals[i] + dyVals[i] - rVals[i] < 0){
			dyVals[i] = -dyVals[i];
		}
		xVals[i] += dxVals[i];
		yVals[i] += dyVals[i];
	}

	glutSwapBuffers();
	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever a key is pressed.
void keyboard(unsigned char c, int x, int y)
{
	switch (c) 
	{
		case 27: // escape character means to quit the program
			exit(0);
			break;
		case 'b':
			// do something when 'b' character is hit.
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void reshape(int w, int h)
{
	// Reset our global variables to the new width and height.
	screen_x = w;
	screen_y = h;

	// Set the pixel resolution of the final picture (Screen coordinates).
	glViewport(0, 0, w, h);

	// Set the projection mode to 2D orthographic, and set the world coordinates:
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
}


int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	int fullscreen = 0;
	if (fullscreen) 
	{
		glutGameModeString("800x600:32");
		glutEnterGameMode();
	} 
	else 
	{
		glutCreateWindow("This appears in the title bar");
	}

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}