#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "../math/random.h"

class Lambertian : public Material {
    public:
        Lambertian(const Color& c) : Material(c) {}
        Direction scatter_direction(const Direction& u, const Direction& normal) const override {
            Direction random_direction = normal + random_unit_vector();
            return random_direction.normalize();
        };
        Color scatter_color(const Color& ray) const override { return ray * albedo; }
};

#endif