#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "hittable.h"
#include "../rendering/camera.h"

class Background {
    public:
        Position center;
        Background(const Camera& c) : center{c.position} {}
        Background() = default;
        ~Background() = default;

        /**
         * @brief Changes the color of the ray who got to the background.
         * Does not change any other property.
         * When rendering the scene, hitting the background should be a stopping
         * condition to not keep shooting the ray.
         * At the moment, the background is a blue gradient, from top to bottom (x axis points up).
         * With a purple floor (x < 0)
         * 
         * @param ray the ray that made contact with the background
         * @return Ray the ray after hitting the background (color shifted)
         */
        Ray scatter_ray_on_hit(const Ray& ray) const {
            Color color;
            double x = ray.direction[0] / ray.direction.length();
            double blue = 1 - min(max(0.5 * (x + 1), 0.0), 1.0);
            color = Color(blue, blue, 1.0);
            return Ray(ray.origin, ray.direction, ray.color*color);
        }
};

#endif