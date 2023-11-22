#ifndef MATERIAL_H
#define MATERIAL_H

#include "../physics/vector.h"

class Material {
    public:
        virtual ~Material() = default;
        virtual Direction scatter_direction(const Direction& u, const Direction& normal) const = 0;
};

#endif