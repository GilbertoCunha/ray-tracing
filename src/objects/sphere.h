#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <optional>
#include "../rendering/global.h"
#include "../physics/transformation.h"
#include "../physics/ray.h"
#include "hittable.h"

class Sphere : public Hittable {
    public:
        Position center;
        Color color;
        double radius;
        Sphere(const Position& center, double radius, const Color& c) : center{center}, radius{radius}, color{c} {};
        Sphere() = default;
        ~Sphere() = default;

        // Hittable methods
        Ray scatter_ray_on_hit(const Ray& ray) const override {
            
            // Perfect reflection
            // calculate normal
            Direction normal = (ray.origin - center);
            normal = normal / normal.length();
            int is_inside = dot(normal, ray.direction) < 0 ? 1 : -1;
            normal = normal * is_inside;

            // calculate outgoing direction
            Rotation rot = Rotation(
                cross(normal, -ray.direction),
                2*angle(normal, ray.direction)
            );
            Direction new_direction = dot(rot, -ray.direction);
            double f = 0.3;
            Color new_color = Color(
                ray.color.red()*(1-f)+color.red()*f,
                ray.color.green()*(1-f)+color.green()*f,
                ray.color.blue()*(1-f)+color.blue()*f
            );

            return Ray(ray.origin, new_direction, new_color);
        }

        /**
         * @brief Calculates the (possible) intersection distance between a ray and a sphere
         * 
         * Let he ray is parameterized as:
         * => Ray = Origin + t * Direction
         * And the sphere has:
         * => Radius = R
         * => Center = C
         * 
         * Then, the intersection between them has solutions t according to the quadratic formula:
         * => t = (-b +- sqrt(b*b - 4*a*c)) / (2 * a)
         * Where:
         * => a = Direction . Direction
         * => b = 2 * (Direction . (Direction - Center))
         * => c = (Direction - Center) . (Direction - Center) - R*R
         * The number of solutions means that:
         * => 0 solutions: They don't intersect
         * => 1 solution: The ray just hits the surface of the sphere
         * => 2 solutions: The ray hits the sphere twice (if we allow it to pass through it)
         * 
         * Note, however, that if t<0, then the intersection point is behind the ray.
         * This is not a valid solution, as the ray goes forward.
         * As such, the intersection point will always be:
         * - A solution to the above equation where t>0
         * - If there is more than one solution, choose the closest (smallest t)
         * 
         * @param ray The incoming ray
         * @return optional<double> The possible intersection distance from ray position to sphere
         */
        optional<double> intersection_distance(const Ray& ray) const override {

            // Calculate quadratic formula a, b and c coefficients
            Direction pos_diff = ray.origin - center;
            double a = dot(ray.direction, ray.direction);
            double b = 2 * dot(ray.direction, pos_diff);
            double c = dot(pos_diff, pos_diff) - radius*radius;

            // Calculate the root
            // The correct root to calculate must
            // 1. Have a positive solution (intersection point is in front of the ray, not behind it)
            // 2. If more than one solution meets criteria 1, choose the closest
            double square = b*b - 4*a*c;
            optional<double> root = nullopt;
            if (square > 0) {
    
                // Calculate the two roots candidates
                double root_candidate_1 = (-b-sqrt(square))/(2*a);
                double root_candidate_2 = (-b+sqrt(square))/(2*a);

                // Choose smallest positive root candidate
                if (root_candidate_1 > 0 && root_candidate_2 > 0) root = min(root_candidate_1, root_candidate_2);
                else if (root_candidate_1 > 0) root = root_candidate_1;
                else if (root_candidate_2 > 0) root = root_candidate_2;

            } else if (square == 0) {
                // Calculate root candidate
                double root_candidate = -b/(2*a);
                // Choose it if it is positive
                if (root_candidate > 0) root = root_candidate;
            }

            // Calculate intersection position
            optional<double> intersection = root.has_value() ? root.value() - EPS : optional<double>{};

            return intersection;
        }

};

ostream& operator<<(ostream& cout, const Sphere& s) {
    cout << "Sphere(\n";
    cout << '\t' << s.center << ",\n";
    cout << '\t' << "Radius(" << s.radius << ')' << ",\n";
    cout << '\t' << s.color << '\n';
    cout << ')';
    return cout;
}

#endif