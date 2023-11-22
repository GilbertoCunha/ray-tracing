#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "../math/random.h"

class Lambertian : public Material {
    public:
        Lambertian() {}
        Direction scatter_direction(const Direction& u, const Direction& normal) const {
            Direction random_direction = normal + random_unit_vector();
            return random_direction.normalize();
        };
};

#endif