#include <cmath>
#include <cstring>
#include <string>
#include <GL/freeglut.h>
#include <cstdlib>
#include <vector>
#include "bezier.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
int gW = 100;
int gH = 100;

std::vector<Bezier> gCurves;
std::vector<Bezier> gCurves4;
std::vector<Bezier> gCurves1;

int point_to_move = -1;
int curve_to_move = 0;
int last_curve = 0;

double x1 = 20;
double yy = 20;//Cant be y1, dont know why
double x2 = 30;
double y2 = 50;
double x3 = 50;
double y3 = 50;
double x4 = 60;
double y4 = 10;
double x5 = 20;
double y5 = 20;

std::vector<int> chosen_colors = {1};



// 
// Functions that draw basic primitives
//


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

/* Uncomment for degree 3
	for(int i=0; i<(int)gCurves.size(); i++){
		int color = chosen_colors[i];
		if(color==1){
			glColor3ub(255,0,0);
		} else if(color==2){
			glColor3ub(0,255,0);
		} else if(color==3){
			glColor3ub(0,0,255);
		} else if(color==4){
			glColor3ub(255,140,0);
		} else if(color==5){
			glColor3ub(0,0,0);
		}
		gCurves[i].DrawCurve();
		gCurves[i].DrawControlPoints();
	}
*/
	for(int i=0; i<(int)gCurves1.size(); i++){
		int color = chosen_colors[i];
		if(color==1){
			glColor3ub(255,0,0);
		} else if(color==2){
			glColor3ub(0,255,0);
		} else if(color==3){
			glColor3ub(0,0,255);
		} else if(color==4){
			glColor3ub(255,140,0);
		} else if(color==5){
			glColor3ub(0,0,0);
		}
		gCurves1[i].DrawCurve1();
		gCurves1[i].DrawControlPoints1();
	}

/*
	for(int i=0; i<(int)gCurves4.size(); i++){
		int color = chosen_colors[i];
		if(color==1){
			glColor3ub(255,0,0);
		} else if(color==2){
			glColor3ub(0,255,0);
		} else if(color==3){
			glColor3ub(0,0,255);
		} else if(color==4){
			glColor3ub(255,140,0);
		} else if(color==5){
			glColor3ub(0,0,0);
		}
		gCurves4[i].DrawCurve4();
		gCurves4[i].DrawControlPoints4();
	}
*/

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
		case 'x':
			gCurves.erase(gCurves.begin()+last_curve);
			chosen_colors.erase(chosen_colors.begin()+last_curve);
			last_curve = 0;
			break;
		case '1':
			chosen_colors[last_curve] = 1;
			break;
		case '2':
			chosen_colors[last_curve] = 2;
			break;
		case '3':
			chosen_colors[last_curve] = 3;
			break;
		case '4':
			chosen_colors[last_curve] = 4;
			break;
		case '5':
			chosen_colors[last_curve] = 5;
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
	gluOrtho2D(0, gW, 0, gH);
	glMatrixMode(GL_MODELVIEW);

}

// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int tx, int ty)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		double xconv = screen_x/(double)gW;
		double yconv = screen_y/(double)gH;

		double x = (double)tx/xconv; 
		double y = (double)ty/yconv; 

		for(int i=0; i<(int)gCurves.size(); i++){
			int p = gCurves[i].IsPicked(x,gH-y);
			if(p!=-1){
				curve_to_move = i;
				point_to_move = p;
				last_curve = i;
			}
		}
		for(int i=0; i<(int)gCurves4.size(); i++){
			int p = gCurves4[i].IsPicked4(x,gH-y);
			if(p!=-1){
				curve_to_move = i;
				point_to_move = p;
				last_curve = i;
			}
		}

		for(int i=0; i<(int)gCurves1.size(); i++){
			int p = gCurves1[i].IsPicked1(x,gH-y);
			if(p!=-1){
				curve_to_move = i;
				point_to_move = p;
				last_curve = i;
			}
		}
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		point_to_move = -1;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
	}
	glutPostRedisplay();
}

void motion(int tx, int ty){
	double xconv = screen_x/(double)gW;
	double yconv = screen_y/(double)gH;

	double x = (double)tx/xconv; 
	double y = (double)ty/yconv; 

	//int p = bezier.IsPicked(x,gH-y);
	/*
	if(point_to_move!=-1){
		gCurves4[curve_to_move].mPoints4[point_to_move].mP[0] = x;
		gCurves4[curve_to_move].mPoints4[point_to_move].mP[1] = gH-y;
	}
	*/

	if(point_to_move!=-1){
		gCurves1[curve_to_move].mPoints1[point_to_move].mP[0] = x;
		gCurves1[curve_to_move].mPoints1[point_to_move].mP[1] = gH-y;
	}

/* Uncomment for degree 3
	if(point_to_move!=-1){
		gCurves[curve_to_move].mPoints[point_to_move].mP[0] = x;
		gCurves[curve_to_move].mPoints[point_to_move].mP[1] = gH-y;
	}
*/
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	Point2 p1(x1,yy);
	Point2 p2(x2,y2);
	Point2 p3(x3,y3);
	Point2 p4(x4,y4);
	Bezier bezier(p1,p2,p3,p4);

	Point4 p5(x1,yy);
	Point4 p6(x2,y2);
	Point4 p7(x3,y3);
	Point4 p8(x4,y4);
	Point4 p9(x5,y5);
	Bezier bezier4(p5,p6,p7,p8,p9);

	Point1 pa(x1,yy);
	Point1 pb(x2,y2);
	Point1 pc(x3,y3);
	Bezier bezier1(pa, pb, pc);
	gCurves1.push_back(bezier1);
	gCurves.push_back(bezier);
	gCurves4.push_back(bezier4);
}

void top_menu(int id){
	if(id==1){
		x1+=5; yy+=5; x2+=5; y2+=5; x3+=5; y3+=5; x4+=5; y4 += 5;
		Point2 p1(x1,yy);
		Point2 p2(x2,y2);
		Point2 p3(x3,y3);
		Point2 p4(x4,y4);
		Bezier bezier(p1,p2,p3,p4);
		gCurves.push_back(bezier);
		if((int)gCurves.size() < 6){
			chosen_colors.push_back((int)gCurves.size());
		} else {
			chosen_colors.push_back((int)gCurves.size()%5);
		}
	}
	if(id==2){
		gCurves.erase(gCurves.begin()+last_curve);
		chosen_colors.erase(chosen_colors.begin()+last_curve);
		last_curve = 0;
	}
}

void color_menu(int id){
	chosen_colors[last_curve] = id;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screen_x, screen_y);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Bezier");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);

	int sub_menu = glutCreateMenu(color_menu);
	glutAddMenuEntry("red",1);
	glutAddMenuEntry("green",2);
	glutAddMenuEntry("blue",3);
	glutAddMenuEntry("orange",4);
	glutAddMenuEntry("black",5);

	glutMotionFunc(motion);
	glutCreateMenu(top_menu);
	glutAddSubMenu("color", sub_menu);
	glutAddMenuEntry("Add", 1);
	glutAddMenuEntry("Del", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}