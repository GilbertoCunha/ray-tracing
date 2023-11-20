#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "../physics/ray.h"
#include "../image_generator/ppm_generator.h"
using namespace std;

using ImageRow = Ray*;
using ImagePlane = ImageRow*;

/**
 * @brief A class for representing a camera
 * We say that the image plane is in the same position as the camera
 * sort of like a grid of pixels, but positioned all in the same place
 * 
 */
class Camera {
    private:
        Position position;
        Direction direction;
        double field_of_view; // Angle between top and bottom of screen in rads
        double aspect_ratio;
        int image_width;
        int image_height;
        ImagePlane image_plane;

    public:
        Camera(
            const Position& p = Position(0.0, 0.0, 0.0),
            const Direction& u = Direction(0.0, 0.0, 1.0),
            double fov = 2/3 * M_PI,
            double aspect_ratio = 16.0 / 9.0,
            int image_height = 720
        ) : position{p}, direction{u}, field_of_view{fov}, aspect_ratio{aspect_ratio}, image_height{image_height} {
            // Calculate image height
            image_width = image_height * aspect_ratio;

            // Calculate rays for the image plane
            image_plane = new ImageRow[image_height];
            for (int i=0; i<image_height; i++) {
                image_plane[i] = new Ray[image_width];
                for (int j=0; j<image_width; j++) {
                    image_plane[i][j] = Ray(p, u, Color(0.0,0.0,1.0));
                }
            }
        }

        void render(string image_path) {
            ofstream image_file;
            image_file.open(image_path);
            write_ppm_header(image_file, image_height, image_width);
            for (int i=0; i<image_height; i++) {
                for (int j=0; j<image_width; j++) {
                    ray_to_ppm(image_file, image_plane[i][j]);
                    image_file << ' ';
                }
                image_file << '\n';
            }
            image_file.close();
        }

};



#endif