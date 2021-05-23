#include "grid.h"


Water::Water(){
    z = -4;
    inc = .005;
}

void Water::Draw(){
    //Handles Transparent Water
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0,0,0,.6);

    z+=inc;
    if(z>=-1.5 || z<=-4){
        inc*=-1;
    }
    //glColor3d(0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0,0); glVertex3f(0,0, z);
    glTexCoord2f(0,10); glVertex3f(0, H, z);
    glTexCoord2f(10,10); glVertex3f(W, H, z);
    glTexCoord2f(10,0); glVertex3f(W, 0, z);
    glEnd();
    glDisable(GL_BLEND);

}

float Water::GetZ(){
    return z;
}

Cell::Cell(){
}

float function( float x, float y){
    float z = 0;
    float zscale = .45;
    z += 1.3*sin(.8*y);
    z += 1.1*cos(.1*x);
    z += 9*sin(.14*x)*cos(.2*y);
    return z*zscale;
}


void Cell::Draw(double x, double y){
    int red = ((int)(x+1)*345522 + (int)(y+1)*4353534)%256;
    int green = ((int)(x+1)*83928 + (int)(y+1)*738948)%256;
    int blue = ((int)(x+1)*29130 + (int)(y+1)*839203)%256;
    int div = 25;
    glColor3ub(red, green, blue);
    glBegin(GL_QUADS);
    glTexCoord2f(x/div,y/div); glVertex3f(x,y, function(x,y));
    glTexCoord2f(x/div,(y+1)/div); glVertex3f(x, y+1, function(x,y+1));
    glTexCoord2f((x+1)/div,(y+1)/div); glVertex3f(x+1, y+1, function(x+1,y+1));
    glTexCoord2f((x+1)/div,y/div); glVertex3f(x+1, y, function(x+1,y));
    glEnd();
}

Grid::Grid(){
}

void Grid::Draw(){
    for(int i=0; i<W; i++){
        for(int j=0; j<H; j++){
            mCells[i][j].Draw(i,j);
        }
    }
}

