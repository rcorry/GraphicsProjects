#include "maze.h"
extern viewtype current_view;

Cell::Cell(){
    l = t = r = b = true;
    v = false;
}

void Cell::Draw(double x, double y){
    int red = ((int)(x+1)*345522 + (int)(y+1)*4353534)%256;
    int green = ((int)(x+1)*83928 + (int)(y+1)*738948)%256;
    int blue = ((int)(x+1)*29130 + (int)(y+1)*839203)%256;
    glColor3ub(red, green, blue);

    if(current_view == top_view) 
    {
        if (l){
            DrawLine(x, y, x, y+1);
        }
        if (b){
            DrawLine(x, y, x+1, y);
        }
        if (t){
            DrawLine(x, y+1, x+1, y+1);
        }
        if (r){
            DrawLine(x+1, y, x+1, y+1);
        }
    }
    else
    {
        if(l){
            glBegin(GL_QUADS);
	        glTexCoord2f(0,1); glVertex3d(x,y,0); 
	        glTexCoord2f(1,1); glVertex3d(x,y+1,0);
	        glTexCoord2f(1,0); glVertex3d(x,y+1,1);
	        glTexCoord2f(0,0); glVertex3d(x,y,1);
            glEnd();
        }
        if(r){
            glBegin(GL_QUADS);
	        glTexCoord2f(0,1); glVertex3d(x+1,y,0); // All of Sandra
	        glTexCoord2f(1,1); glVertex3d(x+1,y+1,0);
	        glTexCoord2f(1,0); glVertex3d(x+1,y+1,1);
	        glTexCoord2f(0,0); glVertex3d(x+1,y,1);
            glEnd();

        }
        if(t){
            glBegin(GL_QUADS);
	        glTexCoord2f(0,1); glVertex3d(x,y+1,0); // All of Sandra
	        glTexCoord2f(1,1); glVertex3d(x+1,y+1,0);
	        glTexCoord2f(1,0); glVertex3d(x+1,y+1,1);
	        glTexCoord2f(0,0); glVertex3d(x,y+1,1);
            glEnd();
        }
        if(b){
            glBegin(GL_QUADS);
	        glTexCoord2f(0,1); glVertex3d(x,y,0); // All of Sandra
	        glTexCoord2f(1,1); glVertex3d(x+1,y,0);
	        glTexCoord2f(1,0); glVertex3d(x+1,y,1);
	        glTexCoord2f(0,0); glVertex3d(x,y,1);
            glEnd();

        }
    }
}


Maze::Maze(){
    srand(time(0));
    RemoveWalls();
}

void Maze::Draw(){
    glColor3d(1,1,1);
    for(int i=0; i<W; i++){
        for(int j=0; j<H; j++){
            mCells[i][j].Draw(i,j);
        }
    }
    srand(0);
}

void Maze::RemoveWalls(){
    RemoveWallsRecursive(0,0);

}

void Maze::DrawBackground(){
    glBegin(GL_QUADS);
	glTexCoord2f(0,5); glVertex2d(0, H); 
	glTexCoord2f(5,5); glVertex2d(W, H);
	glTexCoord2f(5,0); glVertex2d(W, 0);
	glTexCoord2f(0,0); glVertex2d(0,0);
    glEnd();
}
void Maze::RemoveWallsRecursive(int i, int j){
    mCells[i][j].v = true;
    enum NEIGHBORS {LEFT, TOP, RIGHT, BOTTOM};
    while(true){
        std::vector<NEIGHBORS> n;

        if(i>0 and mCells[i-1][j].v == false){
            n.push_back(LEFT);
        }
        if(i<(W-1) and mCells[i+1][j].v == false){
            n.push_back(RIGHT);
        }
        if(j>0 and mCells[i][j-1].v == false){
            n.push_back(BOTTOM);
        }
        if(j<(H-1) and mCells[i][j+1].v == false){
            n.push_back(TOP);
        }

        if(n.size() == 0){
            return;
        }

        int r = rand() % n.size();

        if(n[r] == LEFT){
            mCells[i][j].l = false;
            mCells[i-1][j].r = false;
            RemoveWallsRecursive(i-1,j);
        }
        if (n[r] == RIGHT){
            mCells[i][j].r = false;
            mCells[i+1][j].l = false;
            RemoveWallsRecursive(i+1, j);
        }
        if (n[r] == TOP){
            mCells[i][j].t = false;
            mCells[i][j+1].b = false;
            RemoveWallsRecursive(i, j+1);
        }
        if (n[r] == BOTTOM){
            mCells[i][j].b = false;
            mCells[i][j-1].t = false;
            RemoveWallsRecursive(i, j-1);
        }
    }
}

bool Maze::OnWall(double x, double y, double rad) const {
    int i = (int)x;
    int j = (int)y;

    double offsetx = x - i;

    double offsety = y - j;

    if(mCells[i][j].l && offsetx - rad < 0){
        return true;
    }
    if(mCells[i][j].r && offsetx + rad > 1){
        return true;
    }
    if(mCells[i][j].b && offsety - rad < 0){
        return true;
    }
    if(mCells[i][j].t && offsety + rad > 1){
        return true;
    }
    if(offsetx-rad < 0 && offsety+rad > 1){
        return true;
    }
    if(offsetx-rad < 0 && offsety-rad < 0){
        return true;
    }
    if(offsetx+rad > 1 && offsety+rad > 1){
        return true;
    }
    if(offsetx+rad > 1 && offsety+rad < 0){
        return true;
    }
    return false;

}


void Maze::DrawET(int x, int y){
    glBegin(GL_QUADS);
	glTexCoord2f(1,0); glVertex3d(x, y+1,.05); 
	glTexCoord2f(0,0); glVertex3d(x+1, y+1,.05);
	glTexCoord2f(0,1); glVertex3d(x+1, y,.05);
	glTexCoord2f(1,1); glVertex3d(x,y,.05);
    glEnd();
}
