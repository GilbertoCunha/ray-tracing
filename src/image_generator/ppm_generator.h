#ifndef PPM_GENERATOR_H
#define PPM_GENERATOR_H

#include "../physics/ray.h"
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Write a PPM header to define parameters of PPM image.
 * Has to write:
 * P3 to tell the image to use ASCII colors
 * [image_width] [image_height] to tell it image dimensions
 * [max_pixel_color] to tell the color ranges to the image
 * 
 * @param image_file The ppm file to write to
 * @param image_height The height of the image
 * @param image_width The width of the image
 */
void write_ppm_header(ofstream& image_file, int image_height, int image_width) {
    image_file << "P3\n";
    image_file << image_width << ' ' << image_height << '\n';
    image_file << "255\n";
}

/**
 * @brief Writes a single pixel to a PPM file
 * 
 * @param image_file The ppm image file
 * @param pixel The pixel to writ to the image
 */
void ray_to_ppm(ofstream& image_file, const Ray& ray) {
    image_file << ray.color.to_ppm();
}

#endif