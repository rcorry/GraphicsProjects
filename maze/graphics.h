#ifndef GRAPHICS
#define GRAPHICS
#include "maze.h"
#include "rat.h"
#include <cmath>
#include <cstring>
#include <GL/freeglut.h>

enum viewtype{top_view, perspective_view, rat_view};

void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawLine(double x1, double y1, double x2, double y2);
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawEllipse(int x,int y,float StAngle,float EndAngle,int RX, int RY);
void DrawCircle(double x1, double y1, double radius);
void SetTopView(int w, int h);
void SetPerspectiveView(int w, int h);

#endif //GRAPHICS
