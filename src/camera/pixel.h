#ifndef PIXEL_H
#define PIXEL_H

#include "../materials/color.h"
#include "../physics/vector.h"
using namespace std;

class Pixel {
    public:
        Color color;
        Position position;
        Pixel(Color c, Position p) : color{c}, position{p} {}
        string to_ppm() { return color.to_ppm(); }
};

#endif