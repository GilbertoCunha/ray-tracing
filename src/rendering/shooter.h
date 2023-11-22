#ifndef SHOOTER_H
#define SHOOTER_H

#include "camera.h"
#include "../logs/progress_bar.h"
#include "../physics/ray.h"
#include "../math/random.h"

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

            cout << "Creating camera rays...\n";
            for (int i=0; i<c.image_height; i++) {

                progress_bar(cout, i+1, image_height);

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

/**
 * @brief A class that generates one ray per pixel, shot right through the pixel's center
 * 
 */
class AntiAliasingRayShooter : public RayShooter {
    public:
        AntiAliasingRayShooter(const Camera& c, int rays_per_pixel) {

            // Set attributes
            image_height = c.image_height;
            image_width = c.image_width;
            this->rays_per_pixel = rays_per_pixel;

            // Calculate rays for the image plane
            double angle_vert_delta = c.field_of_view / c.image_height;
            double angle_hor_delta = c.aspect_ratio * c.field_of_view / c.image_width;
            double angle_vert_upper = 0.5 * c.field_of_view;
            double angle_hor_upper;
            Direction rot_x;
            Rotation rot_vert, rot_hor;
            rays = new Ray**[c.image_height];

            cout << "Creating camera rays...\n";
            for (int i=0; i<c.image_height; i++) {

                progress_bar(cout, i+1, image_height);

                // Mean angle of rotation around y axis
                rays[i] = new Ray*[c.image_width];
                angle_vert_upper -= angle_vert_delta;
                angle_hor_upper = 0.5 * c.field_of_view * c.aspect_ratio;

                for (int j=0; j<c.image_width; j++) {

                    // Mean angle of rotation around x axis
                    angle_hor_upper -= angle_hor_delta;
                    rays[i][j] = new Ray[rays_per_pixel];

                    for (int k=0; k<rays_per_pixel; k++) {

                        // Calculate random rotations
                        rot_vert = Rotation(
                            Direction(0.0, 1.0, 0.0),
                            random_uniform(
                                angle_vert_upper - angle_vert_delta, 
                                angle_vert_upper
                            )
                        );
                        rot_hor = Rotation(
                            Direction(1.0, 0.0, 0.0),
                            random_uniform(
                                angle_hor_upper - angle_hor_delta, 
                                angle_hor_upper
                            )
                        );

                        // Create ray
                        rays[i][j][k] = Ray(
                            c.position,
                            dot(rot_hor, dot(rot_vert, c.direction)),
                            Color(1.0, 1.0, 1.0) // Color of initial rays is the null element of multiplication
                        );
                    }

                }
            }
        }
};

#endif