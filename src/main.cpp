#include <iostream>
#include <fstream>
using namespace std;

#include "camera/pixel.h"
#include "image_generator/ppm_generator.h"
#include "logs/progress_bar.h"
#include "image_generator/ppm_generator.h"

/**
 * @brief Main function. Generates and renders the whole scene.
 * 
 * @return int Success of the function (0 => success, 1 => failure)
 */
int main () {

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

    return 0;
}