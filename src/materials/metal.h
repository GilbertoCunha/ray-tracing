#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "../physics/transformation.h"

class Metal : public Material {
    public:
        Metal(const Color& c) : Material(c) {}
        Direction scatter_direction(const Direction& u, const Direction& normal) const override {
            Direction new_direction = u - normal * u.dot(normal) * 2;
            return new_direction.normalize();
        }
        Color scatter_color(const Color& ray) const override { return ray * albedo; }
};

#endif