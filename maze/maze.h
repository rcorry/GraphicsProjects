#ifndef MAZE
#define MAZE
#include "graphics.h"
#include <iostream>
#include <vector>
#include <random>


const int W = 8;
const int H = 6;

class Cell {

public:
    Cell();
    bool l, t, r, b;
    bool v;
    void Draw(double x, double y);

private:
};

class Maze {

public:
    Maze();
    void Draw();
    void RemoveWalls();
    void RemoveWallsRecursive(int i, int j);
    bool OnWall(double x, double y, double rad) const;
    void DrawBackground();
    void DrawET(int x, int y);

private:
    Cell mCells[W][H];
};

#endif //MAZE
