#include <iostream>
#include <fstream>
using namespace std;

#include "camera/pixel.h"
#include "image_generator/ppm_generator.h"
#include "logs/progress_bar.h"
#include "image_generator/ppm_generator.h"
#include "math/vector.h"
#include "physics/ray.h"
#include "materials/color.h"
#include "objects/sphere.h"
#include <optional>

/**
 * @brief Main function. Generates and renders the whole scene.
 * 
 * @return int Success of the function (0 => success, 1 => failure)
 */
int main () {

    // Create Ray and Sphere
    Ray ray = Ray(
        Position(0.0, 0.0, 0.0),
        Direction(0.0, 0.0, 1.0),
        Color(1.0, 1.0, 1.0)
    );
    Sphere sphere = Sphere(
        Position(0.0, 0.0, 0.0),
        1.0
    );
    cout << '\n';
    cout << "###################";
    cout << "# CREATED OBJECTS #";
    cout << "###################";
    cout << '\n';
    cout << ray;
    cout << sphere;

    optional<Position> intersection = sphere.intersection_position(ray);
    cout << '\n';
    cout << "################";
    cout << "# INTERSECTION #";
    cout << "################";
    cout << '\n';
    if (intersection.has_value()) {
        cout << intersection.value();
    } else {
        cout << "No intersection found.";
    }


    /*
    // Open image file to write to
    ofstream image_file;
    image_file.open("result.ppm");

    // Define image properties
    int image_height = 256;
    int image_width = 256;

    // Initialize PPM file header
    write_ppm_header(image_file, image_height, image_width);

    // Write all pixels to PPM
    for (int i=0; i<image_height; i++) {
        progress_bar(clog, i+1, image_height);
        for (int j=0; j<image_width; j++) {
            Pixel pixel = Pixel(
                double(i) / image_height,
                double(j) / image_width,
                0.0
            );
            pixel_to_ppm(image_file, pixel);
            image_file << ' ';
        }
        image_file << '\n';
    }

    // Close file
    image_file.close();
    */

    return 0;
}