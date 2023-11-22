#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "../physics/vector.h"

class Material {
    public:
        Color albedo;
        Material(const Color& c) : albedo{c} {}
        virtual ~Material() = default;
        virtual Direction scatter_direction(const Direction& u, const Direction& normal) const = 0;
        virtual Color scatter_color(const Color& ray) const = 0;
};

#endif