#ifndef METAL_H
#define METAL_H

#include "material.h"
#include "../physics/transformation.h"

class Metal : public Material {
    public:
        Metal() {}
        Direction scatter_direction(const Direction& u, const Direction& normal) const override {
            // Perfect reflection:
            return u - normal * 2 * dot(u, normal);
        }
};

#endif