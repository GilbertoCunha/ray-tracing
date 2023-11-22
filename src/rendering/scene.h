#ifndef SCENE_H
#define SCENE_H

#include <vector>
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
        /* TODO: I get 'free(): invalid pointer' error if this is not commented
        ~Scene() { 
            for (Hittable* object : objects) {
                if (object != nullptr) {
                    delete object;
                    object = nullptr;
                }
            }
        }*/

        void add_object(Hittable* object) { 
            // TODO: Check object is not background
            objects.push_back(object);
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

        static Color average_colors(const Color color[], int size) {
            double r=0, g=0, b=0;
            for (int i=0; i<size; ++i) {
                r += color[i].red();
                g += color[i].green();
                b += color[i].blue();
            }
            return Color(r/size, g/size, b/size);
        }

        Color calculate_ray_color(const Ray& r, int max_hits) const {

            Ray ray = r;
            int closest_index;
            optional<double> closest;
            optional<double> distance;
            bool max_hits_reached=false, hit_background=false, go = true;
            int num_objects = objects.size();

            // Calculate ray color based off multiple reflections
            while(go) {

                // Calculate closest intersection to objects
                closest = nullopt;
                for (int i=0; i<num_objects; i++) {
                    distance = (*objects[i]).intersection_distance(ray);

                    bool distance_value_is_smaller = distance.has_value() && closest.has_value() && distance.value() < closest.value();
                    bool closest_has_no_value = distance.has_value() && (!closest.has_value());

                    if (distance_value_is_smaller || closest_has_no_value) {
                        closest = distance;
                        closest_index = i;
                    }
                }

                // If ray hits nothing, hit background
                if (!closest.has_value()) {
                    hit_background = true;
                    ray = background.scatter_ray_on_hit(ray);
                } else {
                    // Refactor color of ray
                    ray = ray.translate(closest.value());
                    ray = (*objects[closest_index]).scatter_ray_on_hit(ray);
                }

                // Stop if max hits have been reached
                // or if ray hit background
                max_hits -= 1;
                max_hits_reached = max_hits == 0;
                if (max_hits_reached || hit_background) go = false;
            }

            return ray.color;
        }

};

#endif