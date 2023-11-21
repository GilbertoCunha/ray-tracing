#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "../physics/ray.h"
#include "../physics/transformation.h"
#include "../image_generators/ppm_generator.h"
using namespace std;

using ImageRow = Ray*;
using ImagePlane = ImageRow*;

/**
 * @brief A class for representing a camera
 * We say that the image plane is in the same position as the camera
 * sort of like a grid of pixels, but positioned all in the same place
 * 
 * The camera has the following orientation:
 * => x points upward
 * => y points to the right
 * => z points to the front
 * 
 */
class Camera {

    public:
        Position position;
        Direction direction;
        double field_of_view; // Angle between top and bottom of screen in rads
        double aspect_ratio;
        int image_width;
        int image_height;

        Camera(
            const Position& p = Position(0.0, 0.0, 1.0),
            const Direction& u = Direction(0.0, 0.0, 1.0),
            double fov = 1.0 / 3.0 * M_PI, // 60 degrees
            double aspect_ratio = 16.0 / 9.0,
            int image_height = 720
        ) : 
        position{p}, 
        direction{u}, 
        field_of_view{fov}, 
        aspect_ratio{aspect_ratio}, 
        image_height{image_height}
        { image_width = image_height * aspect_ratio; }

};



#endif