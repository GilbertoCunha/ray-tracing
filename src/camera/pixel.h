#ifndef PIXEL_H
#define PIXEL_H

#include "../materials/color.h"

class Pixel {
    private:
        Color color;
    public:
        Pixel(double r, double g, double b) : color{Color(r,g,b)} {};
        string to_ppm() { return color.to_ppm(); }
};

#endif