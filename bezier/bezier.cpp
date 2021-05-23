#include "bezier.h"
void DrawLine(double x1, double y1, double x2, double y2)
{
        glBegin(GL_LINES);
        glVertex2d(x1,y1);
        glVertex2d(x2,y2);
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

Point2::Point2(double x, double y){
   mP[0] = x; 
   mP[1] = y; 
}
Point2::Point2(){
   mP[0] = 5; 
   mP[1] = 5; 
}

Point1::Point1(double x, double y){
   mP[0] = x; 
   mP[1] = y; 
}

Point1::Point1(){
   mP[0] = 5; 
   mP[1] = 5; 
}

Point4::Point4(double x, double y){
   mP[0] = x; 
   mP[1] = y; 
}
Point4::Point4(){
   mP[0] = 5; 
   mP[1] = 5; 
}

Bezier::Bezier(Point2 p1,Point2 p2,Point2 p3,Point2 p4){
    mPoints[0] = p1;
    mPoints[1] = p2;
    mPoints[2] = p3;
    mPoints[3] = p4;
}

Bezier::Bezier(Point1 p1,Point1 p2,Point1 p3){
    mPoints1[0] = p1;
    mPoints1[1] = p2;
    mPoints1[2] = p3;
}

Bezier::Bezier(Point4 p1,Point4 p2,Point4 p3,Point4 p4, Point4 p5){
    mPoints4[0] = p1;
    mPoints4[1] = p2;
    mPoints4[2] = p3;
    mPoints4[3] = p4;
    mPoints4[4] = p5;
}

Point2 Bezier::Evaluate(double t){
    Point2 temp;
    for(int i=0; i<2; i++){
        temp.mP[i] = mPoints[0].mP[i]*pow(1-t,3)+
                     3*mPoints[1].mP[i]*pow(1-t,2)*t+
                     3*mPoints[2].mP[i]*(1-t)*t*t+
                     mPoints[3].mP[i]*pow(t,3);
    }
    return temp;
}

Point1 Bezier::Evaluate1(double t){
    Point1 temp;
    for(int i=0; i<2; i++){
        temp.mP[i] = mPoints1[0].mP[i]*pow(1-t,2)+
                     2*mPoints1[1].mP[i]*(1-t)*t+
                     mPoints1[2].mP[i]*t*t;
    }
    return temp;
}

Point4 Bezier::Evaluate4(double t){
    Point4 temp;
    for(int i=0; i<2; i++){
        temp.mP[i] = mPoints4[0].mP[i]*pow(1-t,4)+
                     4*mPoints4[1].mP[i]*pow(1-t,3)*t+
                     6*mPoints4[2].mP[i]*pow(1-t,2)*t*t+
                     4*mPoints4[3].mP[i]*(1-t)*pow(t,3)+
                     mPoints4[4].mP[i]*pow(t,4);
    }
    return temp;
}

void Bezier::DrawCurve(){
    double inc = 1.0/20.0;
    for(double i=0; i<1; i+=inc){
        Point2 p1 = Evaluate(i);
        Point2 p2 = Evaluate(i+inc);
        DrawLine(p1.mP[0], p1.mP[1], p2.mP[0], p2.mP[1]);
    }
}

void Bezier::DrawCurve1(){
    double inc = 1.0/20.0;
    for(double i=0; i<1; i+=inc){
        Point1 p1 = Evaluate1(i);
        Point1 p2 = Evaluate1(i+inc);
        DrawLine(p1.mP[0], p1.mP[1], p2.mP[0], p2.mP[1]);
    }
}

void Bezier::DrawCurve4(){
    double inc = 1.0/20.0;
    for(double i=0; i<1; i+=inc){
        Point4 p1 = Evaluate4(i);
        Point4 p2 = Evaluate4(i+inc);
        DrawLine(p1.mP[0], p1.mP[1], p2.mP[0], p2.mP[1]);
    }
}

void Bezier::DrawControlPoints1(){
    double x1,x2,x3;
    double y1,y2,y3;
    x1 = mPoints1[0].mP[0];
    y1 = mPoints1[0].mP[1];
    x2 = mPoints1[1].mP[0];
    y2 = mPoints1[1].mP[1];
    x3 = mPoints1[2].mP[0];
    y3 = mPoints1[2].mP[1];
    DrawCircle(x1,y1,1);
    DrawCircle(x2,y2,1), 0.0;
    DrawCircle(x3,y3,1);
}


void Bezier::DrawControlPoints(){
    double x1,x2,x3,x4;
    double y1,y2,y3,y4;
    x1 = mPoints[0].mP[0];
    y1 = mPoints[0].mP[1];
    x2 = mPoints[1].mP[0];
    y2 = mPoints[1].mP[1];
    x3 = mPoints[2].mP[0];
    y3 = mPoints[2].mP[1];
    x4 = mPoints[3].mP[0];
    y4 = mPoints[3].mP[1];
    DrawCircle(x1,y1,1);
    DrawCircle(x2,y2,1);
    DrawCircle(x3,y3,1);
    DrawCircle(x4,y4,1);
}

void Bezier::DrawControlPoints4(){
    double x1,x2,x3,x4,x5;
    double y1,y2,y3,y4,y5;
    x1 = mPoints4[0].mP[0];
    y1 = mPoints4[0].mP[1];
    x2 = mPoints4[1].mP[0];
    y2 = mPoints4[1].mP[1];
    x3 = mPoints4[2].mP[0];
    y3 = mPoints4[2].mP[1];
    x4 = mPoints4[3].mP[0];
    y4 = mPoints4[3].mP[1];
    x5 = mPoints4[4].mP[0];
    y5 = mPoints4[4].mP[1];
    DrawCircle(x1,y1,1);
    DrawCircle(x2,y2,1);
    DrawCircle(x3,y3,1);
    DrawCircle(x4,y4,1);
    DrawCircle(x5,y5,1);
}

int Bezier::IsPicked(double x, double y){
    for(int i=0; i<4; i++){
        if(mPoints[i].mP[0]- 1 < x && mPoints[i].mP[0]+ 1 > x){
            if(mPoints[i].mP[1]- 1 < y && mPoints[i].mP[1]+ 1 > y){
                return i;
            }
        }
    }
    return -1;
}

int Bezier::IsPicked4(double x, double y){
    for(int i=0; i<5; i++){
        if(mPoints4[i].mP[0]- 1 < x && mPoints4[i].mP[0]+ 1 > x){
            if(mPoints4[i].mP[1]- 1 < y && mPoints4[i].mP[1]+ 1 > y){
                return i;
            }
        }
    }
    return -1;
}

int Bezier::IsPicked1(double x, double y){
    for(int i=0; i<3; i++){
        if(mPoints1[i].mP[0]- 1 < x && mPoints1[i].mP[0]+ 1 > x){
            if(mPoints1[i].mP[1]- 1 < y && mPoints1[i].mP[1]+ 1 > y){
                return i;
            }
        }
    }
    return -1;
}