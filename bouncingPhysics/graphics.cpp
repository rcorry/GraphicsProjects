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
#include <random>
#include <cstring>
#include <string>
#include <iostream>
#if WIN32
#include "glut.h"
#else // Linux
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>
#include <cmath>
//#include "CollisionPhysics.cpp"
#endif


double F;
double screen_x = 700;
double screen_y = 500;

class Circle{
public:
	Circle();
	void DrawCircle();
	double getx() {return mX;}
	double gety() {return mY;}
	double getradius() {return mRad;}
	double getr() {return mR;};
	double getg() {return mG;};
	double getb() {return mB;};
	double getdx() {return mDX;}
	double getdy() {return mDY;}
	void setx() {mX += mDX;};
	void sety() {mY += mDY;};
	void setdx(double dx) {mDX *= dx;};
	void setdy(double dy) {mDY *= dy;};
	void setDX(double dx) {mDX = dx;};
	void setDY(double dy) {mDY = dy;};
	double getnextx(){return mX + mDX;};
	double getnexty(){return mY + mDY;};
	void Update(int i);

	int mR, mG, mB;
	double mX, mY, mDX, mDY, mRad;
};

Circle::Circle(){

	//srand(time(NULL));
	mRad = rand() % 30 + 18;
	mX = rand() % (int)(screen_x - 2 * mRad) + mRad;
	mY = rand() % (int)(screen_y - 2 * mRad) + mRad;
	mDX = (rand() % 11 + 4) * .01;// rand() % 1 + 1;//rand()/RAND_MAX;
	mDY = (rand() % 11 + 4) * .01;//rand() % 1 + 1;//rand()/RAND_MAX;
	if (rand()%2 == 0){
		mDX *= -1;
		if(rand()%2 == 0){
			mDY *= -1;
		}
	}
	mR = rand()%256;
	mG = rand()%256;
	mB = rand()%256;

}

const int gSize = 5;
Circle circles[gSize];

struct vectortype
{
	double x;
	double y;
};

void Collide(int p1, int p2, Circle particles[])
{
	double COLLISION_FRICTION = 1;
	vectortype en; // Center of Mass coordinate system, normal component
	vectortype et; // Center of Mass coordinate system, tangential component
	vectortype u[2]; // initial velocities of two particles
	vectortype um[2]; // initial velocities in Center of Mass coordinates
	double umt[2]; // initial velocities in Center of Mass coordinates, tangent component
	double umn[2]; // initial velocities in Center of Mass coordinates, normal component
	vectortype v[2]; // final velocities of two particles
	double m[2];	// mass of two particles
	double M; // mass of two particles together
	vectortype V; // velocity of two particles together
	double size;
	int i;

	double xdif=particles[p1].getnextx() - particles[p2].getnextx();
	double ydif=particles[p1].getnexty() - particles[p2].getnexty();

	// set Center of Mass coordinate system
	size=sqrt(xdif*xdif + ydif*ydif);
	xdif/=size; ydif/=size; // normalize
	en.x=xdif;
	en.y=ydif;
	et.x=ydif;
	et.y=-xdif;

	// set u values
	u[0].x=particles[p1].getdx();
	u[0].y=particles[p1].getdy();
	m[0]=particles[p1].getradius()*particles[p1].getradius();
	u[1].x=particles[p2].getdx();
	u[1].y=particles[p2].getdy();
	m[1]=particles[p2].getradius()*particles[p2].getradius();

	// set M and V
	M=m[0]+m[1];
	V.x=(u[0].x*m[0] + u[1].x*m[1])/M;
	V.y=(u[0].y*m[0] + u[1].y*m[1])/M;

	// set um values
	um[0].x=m[1]/M * (u[0].x-u[1].x);
	um[0].y=m[1]/M * (u[0].y-u[1].y);
	um[1].x=m[0]/M * (u[1].x-u[0].x);
	um[1].y=m[0]/M * (u[1].y-u[0].y);

	// set umt and umn values
	for(i=0;i<2;i++)
	{
		umt[i] = um[i].x * et.x + um[i].y * et.y;
		umn[i] = um[i].x * en.x + um[i].y * en.y;
	}

	// set v values
	for(i=0;i<2;i++)
	{
		v[i].x = umt[i] * et.x - umn[i] * en.x + V.x;
		v[i].y = umt[i] * et.y - umn[i] * en.y + V.y;
	}

	// reset particle values
	particles[p1].setDY(v[0].x*COLLISION_FRICTION);
	particles[p1].setDY(v[0].y*COLLISION_FRICTION);
	particles[p2].setDX(v[1].x*COLLISION_FRICTION);
	particles[p2].setDY(v[1].y*COLLISION_FRICTION);

}

void SwapColors(int a, int b){
	int r1 = circles[a].getr();
	int g1 = circles[a].getg();
	int b1 = circles[a].getb();

	int r2 = circles[b].getr();
	int g2 = circles[b].getg();
	int b2 = circles[b].getb();

	circles[a].mR = r2;
	circles[a].mG = g2;
	circles[a].mB = b2;

	circles[b].mR = r1;
	circles[b].mG = g1;
	circles[b].mB = b1;
}

void Circle::Update(int i){
	//Add Gravity Force
	double G = .05;
	mDY -= G;
	//Add air friction force
	mDY *= F; 
	mDX *= F; 
	//check for ball ball collisions
	if(circles[i].getx() + circles[i].getdx() + circles[i].getradius() > screen_x || circles[i].getx() + circles[i].getdx() - circles[i].getradius() < 0 ){
		circles[i].setdx(-1);
	}
	if(circles[i].gety() + circles[i].getdy() + circles[i].getradius() > screen_y || circles[i].gety() + circles[i].getdy() - circles[i].getradius() < 0 ){
		circles[i].setdy(-1);
	}

	double x1 = circles[i].getnextx();
	double y1 = circles[i].getnexty();
	double rad1 = circles[i].getradius();

	for (int j=i+1; j < gSize; j++){
		double x2 = circles[j].getnextx();
		double y2 = circles[j].getnexty();
		double rad2 = circles[j].getradius();
		double x = x2 - x1;
		double y = y2 - y1;
		double d = sqrt(x*x + y*y);

		if (d <= rad1 + rad2){
			SwapColors(i,j);
			Collide(i,j,circles);
		}
	}
}





// 
// Functions that draw basic primitives
//
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

void Circle::DrawCircle(){
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = mX + mRad * cos(theta);
		double y = mY + mRad * sin(theta);
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

	for(int i=0; i<gSize; i++){
		circles[i].Update(i);
	}

	for(int i=0; i<gSize; i++){
		glColor3ub(circles[i].getr(), circles[i].getg(), circles[i].getb());
		circles[i].setx();
		circles[i].sety();
		circles[i].DrawCircle();
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
			F = .999;
			break;
		case 'n':
			F -= .1;
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
	F = .999;
	std::vector<Circle> temp;
	srand(time(0));
	Circle c;
	temp.push_back(c);
	while(temp.size()<gSize){
		Circle c;
 		double x = c.getx();
 		double y = c.gety();
 		double rad = c.getradius();

 		for (int i = 0; i < (int)temp.size(); i++) {
			double mX = temp[i].getx();
			double mY = temp[i].gety();
			double mR = temp[i].getradius();
  			if ( sqrt(pow(mX-x,2) + pow(mY-y,2)) > (rad + mR + 20) ) {
				  if(i==(int)temp.size()-1){
					  temp.push_back(c);
					  break;
				  }
  			} else {
				break;
			}
		}
	}
	for(int i=0; i<(int)temp.size(); i++){
		circles[i] = temp[i];
	}
}




int main(int argc, char **argv)
{
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

