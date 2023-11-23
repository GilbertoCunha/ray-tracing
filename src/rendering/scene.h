#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <tuple>
#include "../logs/progress_bar.h"
#include "../objects/background.h"
#include "../objects/hittable.h"
#include "shooter.h"
using namespace std;

class Scene {
    public:
        Background background;
        vector<Hittable*> objects;

        Scene(const Background& b) : background{background} {}
        Scene() = default;
        ~Scene() = default;

        void add_object(Hittable& object) {
            // TODO: Check object is not background
            objects.push_back(&object);
        }
        
        void render(const RayShooter& shooter, int max_hits, string image_path) const {
            ofstream image_file;
            image_file.open(image_path);
            write_ppm_header(image_file, shooter.image_height, shooter.image_width);

            // Write the color of each pixel to the image
            Color pixel_color;
            Color pixel_colors[shooter.rays_per_pixel];
            for (int i=0; i<shooter.image_height; ++i) {
                progress_bar(cout, i+1, shooter.image_height);
                for (int j=0; j<shooter.image_width; ++j) {
                    for (int k=0; k<shooter.rays_per_pixel; ++k) {
                        pixel_colors[k] = calculate_ray_color(shooter.rays[i][j][k], max_hits);
                    }
                    pixel_color = average_colors(pixel_colors, shooter.rays_per_pixel);
                    image_file << pixel_color.to_ppm() << ' ';
                }
                image_file << '\n';
            }

            image_file.close();
        }

        static Color average_colors(const Color colors[], int size) {
            double r=0, g=0, b=0;
            for (int i=0; i<size; ++i) {
                r += colors[i].red();
                g += colors[i].green();
                b += colors[i].blue();
            }
            return Color(r/size, g/size, b/size);
        }

        /**
         * @brief Calculates the color of a ray
         * 
         * @param r Incoming ray
         * @param max_hits the maximum number of collisions before stopping the render
         * @return Color color of the ray
         */
        Color calculate_ray_color(const Ray& r, int max_hits) const {
            if (max_hits == 0) {
                return Color(0.0, 0.0, 0.0);
            }

            optional<tuple<int, double>> closest = closest_object(r);
            if (!closest.has_value()) { // Ray hit no objects
                return background.get_color(r);
            } else { // Ray has hit an object
                int index = get<0>(closest.value());
                double distance = get<1>(closest.value());
                Ray new_ray = objects[index]->scatter_ray(r.translate(distance));
                return calculate_ray_color(new_ray, max_hits-1);
            }
        }

        /**
         * @brief Return a tuple of closest object index and distance. Returns nullopt if none are hit.
         * 
         * @param r The incoming ray
         * @return optional<tuple<int,double>> index and distance of closest object hit (if any)
         */
        optional<tuple<int,double>> closest_object(const Ray& r) const {
            optional<tuple<int, double>> closest = nullopt;
            optional<double> distance = nullopt;

            for (int i=0; i<objects.size(); i++) {
                distance = objects[i]->intersection_distance(r);

                bool distance_value_is_smaller = distance.has_value() && closest.has_value() && distance.value() < get<1>(closest.value());
                bool closest_has_no_value = distance.has_value() && (!closest.has_value());

                if (distance_value_is_smaller || closest_has_no_value) closest = tuple(i, distance.value());
            }

            return closest;
        }

};

#endif