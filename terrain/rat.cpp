#include "rat.h"


float function1( float x, float y){
    float z = 0;
    float zscale = .45;
    z += 1.3*sin(.8*y);
    z += 1.1*cos(.1*x);
    z += 9*sin(.14*x)*cos(.2*y);
    return z*zscale;
}

Rat::Rat(){
    x = y = 50;
    z = function1(x,y);
    degrees = 0;
    mDX = 0;
    mDY = 0;
}


void Rat::Update(){
    double DT = .1;
    double radians = (degrees / 180) * 3.141592654;
    double dx = cos(radians) * DT;
    double dy = sin(radians) * DT;
    mDX = dx;
    mDY = dy;
    x+=mDX;
    y+=mDY;
    z = function1(x,y);
}

void Rat::SpinLeft(){
    degrees += 5;
    double DT = .1;
    double radians = (degrees / 180) * 3.141592654;
    double dx = cos(radians) * DT;
    double dy = sin(radians) * DT;
    mDX = dx;
    mDY = dy;
}

void Rat::SpinRight(){
    degrees -= 5;
    double DT = .1;
    double radians = (degrees / 180) * 3.141592654;
    double dx = cos(radians) * DT;
    double dy = sin(radians) * DT;
    mDX = dx;
    mDY = dy;
}

float Rat::GetX(){
    return x;
}
float Rat::GetY(){
    return y;
}

double Rat::GetUnscaledDX(){
    return mDX*10;
}
double Rat::GetUnscaledDY(){
    return mDY*10;
}
float Rat::GetZ(float x, float y){
    float h = function1(x,y);
    if(h<wH){
        h = wH;
    } 
    return h+1;
}

void Rat::UpdateHeight( float h){
    wH = h;
}