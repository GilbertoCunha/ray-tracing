#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>
using namespace std;


/**
 * @brief A class representing 3D vectors and useful operations to perform with them
 * 
 */
class Vector {
    private:
        double e[3];
    public:
        Vector(double x, double y, double z) : e{x,y,z} {};

        // Indexing operations
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Vector sum
        Vector operator+(const Vector u) {
            return Vector(
                e[0] + u[0],
                e[1] + u[1],
                e[2] + u[2]
            );
        }
        Vector operator-() { return Vector(-e[0], -e[1], -e[2]); }
        Vector operator-(const Vector u) {
            return Vector(
                e[0] - u[0],
                e[1] - u[1],
                e[2] - u[2]
            );
        }

        // Vector mult and div
        Vector operator*(const double x) {
            return Vector(
                e[0] * x,
                e[1] * x,
                e[2] * x
            );
        }
        Vector operator/(const double x) {
            return Vector(
                e[0] / x,
                e[1] / x,
                e[2] / x
            );
        }

        // Dot and cross product
        static double dot(const Vector u, const Vector v) {
            return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
        }
        static Vector cross(const Vector u, const Vector v) {
            return Vector(
                u[1]*v[2]-u[2]*v[1],
                u[2]*v[0]-u[0]*v[2],
                u[0]*v[1]-u[1]*v[0]
            );
        }

        // Length
        double length() { return sqrt(length_squared()); }
        double length_squared() { return dot(*this, *this); }

        // Vector normalization
        Vector normalize() {
            double len = length();
            return Vector(
                e[0] / len,
                e[1] / len,
                e[2] / len
            );
        }
};

ostream& operator<<(ostream& out, const Vector& v) {
    return out << '[' << v[0] << ", " << v[1] << ", " << v[2] << ']';
}


#endif