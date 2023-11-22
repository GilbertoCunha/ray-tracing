#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "../physics/transformation.h"

class Metal : public Material {
    public:
        Metal(const Color& c) : Material(c) {}
        Direction scatter_direction(const Direction& u, const Direction& normal) const override {
            // Perfect reflection:
            Direction new_direction = u - normal * 2 * dot(u, normal);
            return new_direction.normalize();
        }
        Color scatter_color(const Color& ray) const override { return ray*albedo; }
};

#endif