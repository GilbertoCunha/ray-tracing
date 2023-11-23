#ifndef RAY_H
#define RAY_H

#include <iostream>
#include "direction.h"
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
    public:
        Position origin;
        Direction direction;
        Color color;

        Ray(Position p, Direction k) : origin{p}, direction{k}, color{1.0,1.0,1.0} {};
        Ray(Position p, Direction k, Color c) : origin{p}, direction{k}, color{c} {};
        Ray() = default;

        Ray translate(double distance) const { 
            return Ray(
                origin + direction*distance,
                direction,
                color
            );
         }
         Ray set_direction(const Direction& u) const { return Ray(origin, u, color); }
         Ray set_color(const Color& c) const { return Ray(origin, direction, c); }
         Ray scatter(double distance, const Direction& u, const Color& c) const {
            return translate(distance).set_direction(u).set_color(c);
         }
};

ostream& operator<<(ostream& cout, const Ray& ray) {
    cout << "Ray(\n";
    cout << '\t' << ray.origin << ",\n";
    cout << '\t' << ray.direction << ",\n";
    cout << '\t' << ray.color << '\n';
    cout << ')';
    return cout;
}

#endif