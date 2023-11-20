#ifndef RAY_H
#define RAY_H

#include "../math/vector.h"
#include "../materials/color.h"

/**
 * @brief A class that represents a ray of light
 * 
 * Attributes:
 *  @origin the current position of the ray
 *  @direction the direction the ray is pointing at
 *  @color the current color of the ray
 */
class Ray {
    private:
        Position origin;
        Direction direction;
        Color color;
    public:
        Ray(Position p, Direction k) : origin{p}, direction{k}, color{1.0,1.0,1.0} {};
        Ray(Position p, Direction k, Color c) : origin{p}, direction{k}, color{c} {};

        // Getters
        Position origin() const { return origin; }
        Direction direction() const { return direction; }
        Color color() const { return color; }

        Ray find_next_ray() const { return *this; };
};

#endif