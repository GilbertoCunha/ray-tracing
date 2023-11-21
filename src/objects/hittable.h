#ifndef HITTABLE_H
#define HITTABLE_H

#include <optional>
#include "../physics/ray.h"

class Hittable {
    public:
        virtual ~Hittable() = default;

        /**
         * @brief Function that scatters a ray that has hit the object.
         * This implies changing the ray's direction and color.
         * 
         * @param r the ray to scatter. Its position should be the point of contact with the object.
         * @return Ray the scattered ray: direction and color have been changed.
         */
        virtual Ray scatter_ray_on_hit(const Ray& r) const = 0;

        virtual optional<double> intersection_distance(const Ray& ray) const = 0;

};

#endif