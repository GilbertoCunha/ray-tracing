#ifndef FUZZY_METAL_H
#define FUZZE_METAL_H

#include "../exceptions/value_error.h"
#include "../math/random.h"
#include "material.h"

class FuzzyMetal : public Material {
    public:
        double fuzzyness;
        FuzzyMetal(const Color& albedo, double fuzzyness) : Material(albedo), fuzzyness{fuzzyness} {
            if (fuzzyness >= 1 || fuzzyness <=0) {
                throw ValueError("Fuzzy metal fuzzyness must be between (0, 1).");
            }
        }
        Direction scatter_direction(const Direction& u, const Direction& normal) const override {
            Direction result = u - normal * 2 * u.dot(normal);
            result = result.normalize();
            result += random_unit_vector() * fuzzyness;
            return result.normalize();
        };
        Color scatter_color(const Color& ray) const override { return ray * albedo; }
};

#endif