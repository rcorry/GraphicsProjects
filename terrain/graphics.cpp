#include "graphics.h"
#include <iostream>
using namespace std;

#define STB_IMAGE_IMPLEMENTATION
#include "./StarterTextures2020/stb_image.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "./StarterTextures2020/stb_image.h"


// Global Variables (Only what you need!)
double screen_x = 700;
double screen_y = 500;
double gMargin = .1;

viewtype current_view = top_view;
Grid gGrid;
Rat rat;
bool gLeftButton = false;
bool gMiddleButton = false;
bool gRightButton = false;
const int num_textures = 2;
unsigned int texName[num_textures];
float downward_tilt;

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

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

void DrawLine(double x1, double y1, double x2, double y2)
{
	glBegin(GL_LINES);
	glVertex2d(x1,y1);
	glVertex2d(x2,y2);
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

bool max(int r, int l){
	return r>l;
}

void DrawEllipse(int x,int y,float StAngle,float EndAngle,int RX, int RY)
{
	double i, inc;
	glBegin(GL_LINE_STRIP);
	glColor3f(1,1,0);
	inc=3.14/max(RX,RY)/2;
	i=StAngle;
	while(i<=EndAngle)
	{
		glVertex2f(int((RX*cos(i)+y)+.5),int((RY*sin(i)+x)+.5));
		i=i+inc;
	}
	glEnd();
}


//
// GLUT callback functions
//

// This callback function gets called by the Glut
// system whenever it decides things need to be redrawn.
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_LIGHTING);

	if(current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gGrid.Draw();
		double eye[3] = {100, 50, 0}; // pick a nice vantage point.
		double at[3]  = {0, 100, 1};
		gluLookAt(eye[0], eye[1], eye[2],  at[0], at[1], at[2],  0,0,1); // Z is up!
		
	}
	else if(current_view == top_view)
	{
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else if (current_view == rat_view)
	{
		glLoadIdentity();
		float x = rat.GetX();
		float y = rat.GetY();
		float wH = gGrid.water.GetZ();
		rat.UpdateHeight(wH);
		float z = rat.GetZ(x,y);

		float dx = 2*rat.GetUnscaledDX();
		float dy = 2*rat.GetUnscaledDY();

		float at_x = x + dx;
		float at_y = y + dy;
		float z2 = rat.GetZ(at_x, at_y);
		float at_z = z2 - downward_tilt;
		gluLookAt(x,y,z, at_x, at_y, at_z, 0,0,1);
	}
	if(gLeftButton){
		rat.SpinLeft();
	}
	if(gRightButton){
		rat.SpinRight();
	}
	if(gMiddleButton){
		rat.Update();
	}
	glEnable(GL_DEPTH_TEST);
 	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texName[0]); 
	gGrid.Draw();

	glBindTexture(GL_TEXTURE_2D, texName[1]); 
	gGrid.water.Draw();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
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
		case 'p':
			current_view = perspective_view;
			SetPerspectiveView(screen_x, screen_y);
			break;
		case 't':
			current_view = top_view;
			SetTopView(screen_x, screen_y);
			break;
		case 'r':
			current_view = rat_view;
			SetPerspectiveView(screen_x, screen_y);
			break;
		case 'u':
			downward_tilt-=.2;
			break;
		case 'd':
			downward_tilt+=.2;
			break;
		default:
			return; // if we don't care, return without glutPostRedisplay()
	}

	glutPostRedisplay();
}


// This callback function gets called by the Glut
// system whenever the window is resized by the user.
void SetTopView(int w, int h)
{
	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, 100+world_margin_x, 
		-world_margin_y, 100+world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble) w/(GLdouble) h;
	gluPerspective( 
	/* field of view in degree */ 38.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ .1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}


// reshape:
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	if(current_view == top_view)
	{
		SetTopView(w,h);
	}
	else if(current_view == perspective_view)
	{
		SetPerspectiveView(w,h);
	}
	else // current_view == rat_view
	{
		SetPerspectiveView(w,h);
	}
}


// This callback function gets called by the Glut
// system whenever any mouse button goes up or down.
void mouse(int mouse_button, int state, int x, int y)
{
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		gLeftButton = true;
	}
	if (mouse_button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
	{
		gLeftButton = false;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) 
	{
		gMiddleButton = true;
	}
	if (mouse_button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) 
	{
		gMiddleButton = false;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) 
	{
		gRightButton = true;
	}
	if (mouse_button == GLUT_RIGHT_BUTTON && state == GLUT_UP) 
	{
		gRightButton = false;
	}
	glutPostRedisplay();
}

// Your initialization code goes here.
void InitializeMyStuff()
{
	downward_tilt = 0;
	srand(time(0));
	const char max_file_size = 100;
	char imageFiles[num_textures][max_file_size] = { "./img/moss.jpeg", "./img/water.jpg"};

	glGenTextures(num_textures, texName);

	for(int i=0; i<num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(imageFiles[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			// NOTE: If the above command doesn't work, try it this way:
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
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
	glClearColor(.529, .808, .922, 0); // background color
	InitializeMyStuff();

	glutMainLoop();

	return 0;
}
