#ifndef HITTABLE_H
#define HITTABLE_H

#include <optional>
#include "../physics/ray.h"

class Hittable {
    public:
        virtual ~Hittable() = default;

        /**
         * @brief Function that calculates a new ray after the object is hit.
         * If the object is not hit, returns a nullopt.
         * 
         * @param r The ray of light to check for hitting the object
         * @return optional<Ray> The output ray after hitting the object, if it is hit (nullopt otherwise)
         */
        virtual optional<Ray> scatter_ray_on_hit(const Ray& r) const = 0;

        /**
         * @brief Checks whether or not the object has been hit.
         * 
         * @param scattered_ray Optional scattered ray object. Should be calculated from the `scatter_ray_on_hit` method.
         * @return bool Whether the object was hit or not
         */
        bool hit(const optional<Ray> scattered_ray) const { return scattered_ray.has_value(); }

        /**
         * @brief Calculates the squared distance to the point of the object that was hit (if any)
         * 
         * @param incoming The incoming ray of light that (possibly) scattered on the object
         * @param scattered The (possible) scattered ray of light
         * @return optional<double> The (optional) squared distance between the incoming and scattered rays
         */
        optional<double> hit_distance_squared(const Ray& incoming, const optional<Ray> scattered) const {
            if (hit(scattered)) return 2.0;
            else return nullopt;
        }

};

#endif