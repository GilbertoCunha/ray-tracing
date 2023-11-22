#ifndef HITTABLE_H
#define HITTABLE_H

#include <optional>
#include "../materials/material.h"
#include "../physics/ray.h"

class Hittable {
    public:
        double albedo;
        Color color;
        Material* material;
        virtual ~Hittable() = default;

        /**
         * @brief Calculates the normal between a ray that HAS HIT the object and the object.
         * 
         * @param r Incoming ray that hit the object
         * @return Direction The normal of the object relative to the ray
         */
        virtual Direction calculate_normal(const Ray& r) const = 0;

        /**
         * @brief Calculates the distance between an incoming ray and the object (if they intersect).
         * If they don't intersect, return nullopt
         * 
         * @param ray Incoming ray
         * @return optional<double> Distance between ray and object
         */
        virtual optional<double> intersection_distance(const Ray& ray) const = 0;

        /**
         * @brief Function that scatters a ray that HAS HIT the object.
         * This implies changing the ray's direction and color.
         * It's position does not change since it already hit the object.
         * 
         * @param r Incoming ray. Its position should be the point of contact with the object.
         * @return Ray the scattered ray: direction and color have been changed.
         */
        Ray scatter_ray_on_hit(const Ray& r) const {
            Direction normal = calculate_normal(r);
            return Ray(
                r.origin,
                material->scatter_direction(r.direction, calculate_normal(r)),
                sum_colors(r.color, color, 1-albedo, albedo)
            );
        };

};

#endif