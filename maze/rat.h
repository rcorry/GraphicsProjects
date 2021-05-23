#ifndef RAT
#define RAT

#include "graphics.h"
#include "maze.h"

class Maze;

class Rat {

public:
    Rat();
    void Draw();
    void Update(const Maze &maze);
    void SpinLeft();
    void SpinRight();
    void MoveRight();
    void MoveLeft();
    double GetX();
    double GetY();
    double GetDX();
    double GetDY();

private:
    double x,y, degrees;
    double mDX, mDY;
};

#endif //RAT