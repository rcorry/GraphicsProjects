#include "rat.h"

Rat::Rat(){
    x = y = .5;
    degrees = 0;
    mDX = 0;
    mDY = 0;
}

void Rat::Draw(){
    glPushMatrix();
    glTranslated(x, y, 0);
    glRotatef(degrees, 0, 0, 1);

    //Main Circle
    glColor3ub(100, 100, 100);
    DrawCircle(0, 0, .3);

    //Middle Circle
    glColor3ub(173, 216, 250);
    DrawCircle(0, 0, .15);

    //Smaller Circles
    glColor3d(.9, 1, 0);
    DrawCircle(.25, 0, .05);
    DrawCircle(-.25, 0, .05);
    DrawCircle(0, .25, .05);
    DrawCircle(0, -.25, .05);
    double mx = .25*cos(47.9);
    double my = .25*sin(47.9);
    DrawCircle(mx, my, .05);
    DrawCircle(-mx, my, .05);
    DrawCircle(mx, -my, .05);
    DrawCircle(-mx, -my, .05);

    glColor3ub(0,180,0);
    DrawTriangle(.1, 0, -.08, -.08, -.08, .08);

    glPopMatrix();
}

void Rat::Update(const Maze &maze){
    double DT = .01;
    double radians = (degrees / 180) * 3.141592654;
    double dx = cos(radians) * DT;
    double dy = sin(radians) * DT;
    mDX = dx;
    mDY = dy;
    if(!maze.OnWall(x+dx, y+dy, .37)){
        x += dx;
        y += dy;
    }
    if(!maze.OnWall(x+dx, y, .37)){
        x += dx;
    }
    if(!maze.OnWall(x, y+dy, .37)){
        y += dy; 
    }
}

void Rat::SpinLeft(){
    degrees += 1;
    double DT = .01;
    double radians = (degrees / 180) * 3.141592654;
    double dx = cos(radians) * DT;
    double dy = sin(radians) * DT;
    mDX = dx;
    mDY = dy;
}

void Rat::SpinRight(){
    degrees -= 1;
    double DT = .01;
    double radians = (degrees / 180) * 3.141592654;
    double dx = cos(radians) * DT;
    double dy = sin(radians) * DT;
    mDX = dx;
    mDY = dy;
}

void Rat::MoveRight(){
    x += mDX;
}
void Rat::MoveLeft(){
    x -= mDX;
}

double Rat::GetX(){
    return x;
}
double Rat::GetY(){
    return y;
}
double Rat::GetDX(){
    return mDX;
}
double Rat::GetDY(){
    return mDY;
}
