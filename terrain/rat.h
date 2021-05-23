#ifndef RAT
#define RAT
#include "graphics.h"


class Rat {

public:
    Rat();
    void Draw();
    void Update();
    void UpdateHeight(float wH);
    void SpinLeft();
    void SpinRight();
    float GetX();
    float GetY();
    double GetUnscaledDX();
    double GetUnscaledDY();
    float GetZ(float x, float y);

private:
    double degrees;
    double mDX, mDY;
    float x,y,z, wH;
};

#endif //RAT