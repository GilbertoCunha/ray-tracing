#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "../physics/transformation.h"

class Metal : public Material {
    public:
        Metal() {}
        Direction scatter_direction(const Direction& u, const Direction& normal) const override {
            // Perfect reflection:
            // rotate incoming direction
            // around a perpendicular axis (cross product)
            // by an angle of 2 * angle between u and normal
            Rotation rot = Rotation(
                cross(normal, -u),
                2*angle(normal, u)
            );
            return dot(rot, -u);
        }
};

#endif