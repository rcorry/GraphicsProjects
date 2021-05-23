#include <cmath>
#include <GL/freeglut.h>
#include <iostream>
class Point2 {
public: 
    Point2(double x, double y);
    Point2();
    double mP[2];
private:
};

class Point4 {
public: 
    Point4(double x, double y);
    Point4();
    double mP[2];
private:
};

class Point1 {
public: 
    Point1(double x, double y);
    Point1();
    double mP[2];
private:
};

class Bezier {
public:
    Bezier(Point2 p1,Point2 p2,Point2 p3,Point2 p4);
    Bezier(Point1 p1,Point1 p2,Point1 p3);
    Bezier(Point4 p1,Point4 p2,Point4 p3,Point4 p4, Point4 p5);
    Point2 Evaluate(double t);
    Point4 Evaluate4(double t);
    Point1 Evaluate1(double t);
    void DrawCurve();
    void DrawCurve4();
    void DrawCurve1();
    void DrawControlPoints();
    void DrawControlPoints4();
    void DrawControlPoints1();
    int IsPicked(double x, double y);
    int IsPicked4(double x, double y);
    int IsPicked1(double x, double y);
    Point2 mPoints[4];
    Point4 mPoints4[5];
    Point1 mPoints1[3];

private:
};