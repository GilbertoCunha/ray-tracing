#ifndef PIXEL_H
#define PIXEL_H

#include "../materials/color.h"

class Pixel : public Color {
    public:
        Pixel(double r, double g, double b) : Color(r,g,b) {}
};

#endif