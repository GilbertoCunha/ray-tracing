#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <optional>
#include "../math/vector.h"
#include "../physics/ray.h"
#include "hittable.h"

class Sphere : public Hittable {
    public:
        Position position;
        double radius;
        Sphere(Position position, double radius) : position{position}, radius{radius} {};

        // Hittable methods
        optional<Ray> scatter_ray_on_hit(const Ray& ray) const override {

            // Find ray intersection position
            double linear_coeff;

            // Find ray intersection normal
            // if ray is inside sphere, normal points inward
            // if ray is outside sphere, normal points outward
            // TODO: make sure intersection position STAYS inside
            // or outside of object to avoid double collision

            // For the moment, perfectly reflect the ray

            return nullopt;
        }

        /**
         * @brief Calculates the (possible) intersection point between a ray and a sphere
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
         * @return optional<Position> The possible intersection point in the sphere
         */
        optional<Position> intersection_position(const Ray& ray) const {

            // Calculate quadratic formula a, b and c coefficients
            Direction pos_diff = ray.origin - position;
            double a = Direction::dot(ray.direction, ray.direction);
            double b = 2 * Direction::dot(ray.direction, pos_diff);
            double c = Direction::dot(pos_diff, pos_diff) - radius*radius;

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
            optional<Position> intersection = nullopt;
            if (root.has_value()) {
                intersection = ray.origin + ray.direction * root.value();
            }

            return intersection;
        }

};

ostream& operator<<(ostream& cout, const Sphere& s) {
    cout << "Sphere(\n";
    cout << '\t' << s.position << ",\n";
    cout << '\t' << s.radius << '\n';
    cout << ')';
    return cout;
}

#endif