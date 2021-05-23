#ifndef GRID
#define GRID
#include <iostream>
#include <vector>
#include <random>
#include "graphics.h"

const int W = 100;
const int H = 100;

float function( float x, float y);
class Water {
public:
    Water();
    void Draw();
    float GetZ();
private:
    float z;
    float inc;
};

class Cell {

public:
    Cell();
    void Draw(double x, double y);
private:
};

class Grid {

public:
    Grid();
    void Draw();
    Water water;
private:
    Cell mCells[W][H];
};

#endif //GRID