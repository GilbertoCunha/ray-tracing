#ifndef SPHERE_H
#define SPHERE_H

#include "../math/vector.h"

class Sphere {
    public:
        Position position;
        double radius;
        Sphere(Position position, double radius) : position{position}, radius{radius} {};
};

#endif