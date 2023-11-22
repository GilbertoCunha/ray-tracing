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
         * @brief Calculates color of background
         * 
         * @param ray the ray that made contact with the background
         * @return Ray the ray after hitting the background (color shifted)
         */
        Color get_color(const Ray& ray) const {
            Color color;
            double x = ray.direction[0] / ray.direction.length();
            double blue = 1 - min(max(0.5 * (x + 1), 0.0), 1.0);
            color = Color(blue, blue, 1.0);
            return ray.color*color;
        }
};

#endif