#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "sphere.h"

class Background : public Sphere {
    public:
        Background(const Position& p, double radius) : Sphere(p, radius, Color(1.0, 1.0, 1.0)) {}
        Background() = default;

        /**
         * @brief Changes the color of the ray who made contact.
         * Does not change any other property.
         * When rendering the scene, hitting the background should be a stopping
         * condition to not keep shooting the ray.
         * At the moment, the background is a blue gradient, from top to bottom (x axis points up).
         * With a purple floor (x < 0)
         * 
         * @param ray the ray that made contact with the background
         * @return Ray the ray with the color of the background
         */
        Ray scatter_ray_on_hit(const Ray& ray) const override {
            Color color;
            Direction u = ray.origin - center;
            double x = u[0] / u.length();

            if (x < 0) {
                color = Color(0.6, 0.4, 0.7);
            } else {
                double blue = 1 - min(max(0.5 * (x + 1), 0.0), 1.0);
                color = Color(blue, blue, 1.0);
            }

            return Ray(ray.origin, ray.direction, ray.color*color);
        }

};

#endif