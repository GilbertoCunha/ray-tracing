#ifndef SHOOTER_H
#define SHOOTER_H

#include "camera.h"
#include "../physics/ray.h"

/**
 * @brief A class that generates the rays that are going to be shot to define the final image.
 * It defines three channels:
 * - First channel defines the row of the image plane that the ray is at
 * - Second channel defines the column of the image plane. Together with the first channel, it defines a "pixel" of the image plane
 * - Third channel defines multiple rays that are shot per pixel. This allows for de-noising through techniques like anti-aliasing.
 * 
 */
class RayShooter {
    public:
        int image_height;
        int image_width;
        int rays_per_pixel;
        Ray*** rays;
        virtual ~RayShooter() = default;
};

/**
 * @brief A class that generates one ray per pixel, shot right through the pixel's center
 * 
 */
class GridRayShooter : public RayShooter {
    public:
        GridRayShooter(const Camera& c) {

            // Set attributes
            image_height = c.image_height;
            image_width = c.image_width;
            rays_per_pixel = 1;

            // Calculate rays for the image plane
            double angle_vert, angle_hor;
            Direction rot_x;
            Rotation rot_vert, rot_hor;
            rays = new Ray**[c.image_height];

            for (int i=0; i<c.image_height; i++) {

                // Rotate around y axis to find direction of pixel
                rays[i] = new Ray*[c.image_width];
                angle_vert = (0.5 - double(i) / c.image_height) * c.field_of_view;
                rot_vert = Rotation(Direction(0.0, 1.0, 0.0), angle_vert);

                for (int j=0; j<c.image_width; j++) {

                    // Rotate around x axis
                    angle_hor = (0.5 - double(j) / c.image_width) * c.field_of_view * c.aspect_ratio;
                    rot_hor = Rotation(Direction(1.0, 0.0, 0.0), angle_hor);

                    rays[i][j] = new Ray[1];
                    rays[i][j][0] = Ray(
                        c.position,
                        dot(rot_hor, dot(rot_vert, c.direction)),
                        Color(1.0, 1.0, 1.0) // Color of initial rays is the null element of multiplication
                    );

                }
            }
        }
};

#endif