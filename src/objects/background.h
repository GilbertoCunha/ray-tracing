#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "sphere.h"

class Background : public Sphere {
    public:
        Background(const Position& p, double radius) : Sphere(p, radius) {}
        Background() = default;

        /**
         * @brief Changes the color of the ray who made contact.
         * Does not change any other property.
         * When rendering the scene, hitting the background should be a stopping
         * condition to not keep shooting the ray.
         * At the moment, the background is a blue gradient, from top to bottom (x axis points up).
         * 
         * @param ray the ray that made contact with the background
         * @return Ray the ray with the color of the background
         */
        Ray scatter_ray_on_hit(const Ray& ray) const override {
            Direction u = ray.origin - center;
            double x = u[0] / u.length();
            double blue = 1 - min(max(0.5 * (x + 1), 0.0), 1.0);
            return Ray(
                ray.origin,
                ray.direction,
                Color(blue, blue, 1.0)
            );
        }

};

#endif