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
        Vector operator+(const Vector& u) const {
            return Vector(
                e[0] + u[0],
                e[1] + u[1],
                e[2] + u[2]
            );
        }
        Vector& operator+=(const Vector& u) {
            e[0] += u[0];
            e[1] += u[1];
            e[2] += u[2];
            return *this;
        }
        Vector operator-() const { return Vector(-e[0], -e[1], -e[2]); }
        Vector operator-(const Vector& u) const {
            return Vector(
                e[0] - u[0],
                e[1] - u[1],
                e[2] - u[2]
            );
        }
        Vector& operator-=(const Vector& u) {
            e[0] -= u[0];
            e[1] -= u[1];
            e[2] -= u[2];
            return *this;
        }

        // Vector mult and div
        Vector operator*(double x) const {
            return Vector(
                e[0] * x,
                e[1] * x,
                e[2] * x
            );
        }
        Vector& operator*=(double x) {
            e[0] *= x;
            e[1] *= x;
            e[2] *= x;
            return *this;
        }
        Vector operator/(double x) const {
            return Vector(
                e[0] / x,
                e[1] / x,
                e[2] / x
            );
        }
        Vector& operator/=(double x) {
            e[0] /= x;
            e[1] /= x;
            e[2] /= x;
            return *this;
        }

        // Dot and cross product
        static double dot(const Vector& u, const Vector& v) {
            return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
        }
        static Vector cross(const Vector& u, const Vector& v) {
            return Vector(
                u[1]*v[2]-u[2]*v[1],
                u[2]*v[0]-u[0]*v[2],
                u[0]*v[1]-u[1]*v[0]
            );
        }

        // Length
        double length() const { return sqrt(length_squared()); }
        double length_squared() const { return dot(*this, *this); }

        // Vector normalization
        Vector normalize() const {
            double len = length();
            return Vector(
                e[0] / len,
                e[1] / len,
                e[2] / len
            );
        }
};

ostream& operator<<(ostream& out, const Vector& v) {
    return out << "Vector(" << v[0] << ", " << v[1] << ", " << v[2] << ')';
}

// Create distinct classnames for Position and Direction
// They can and should operate with each other
// Distinguishing them is just to make it more evident of the interpretation
// using Position = Vector;
class Direction : public Vector {
    public:
        Direction(double x, double y, double z) : Vector(x,y,z) {};
};

ostream& operator<<(ostream& out, const Direction& v) {
    return out << "Direction(" << v[0] << ", " << v[1] << ", " << v[2] << ')';
}

/**
 * @brief Class representing a distance.
 * Mostly the same as the vector class, but can now calculate the distance between two positions.
 * We could also calculate distances between vectors, but:
 *  - If you interpret vectors as directional entities with no strict position
 * Then it makes no sense to calculate the distance between two vectors (they have no position)
 * 
 */
class Position : public Vector {
    public:
        Position(double x, double y, double z) : Vector(x,y,z) {}

        // Add positions and directions
        // always returns a position
        Position operator+(const Direction& k) const {
            return Position(
                (*this)[0] + k[0],
                (*this)[1] + k[1],
                (*this)[2] + k[2]
            );
        }
        Position& operator+=(const Direction& k) {
            (*this)[0] += k[0];
            (*this)[1] += k[1];
            (*this)[2] += k[2];
            return (*this);
        }
        Position operator-(const Direction& k) const { 
            return Position(
                (*this)[0] - k[0],
                (*this)[1] - k[1],
                (*this)[2] - k[2]
            );
         }
        Position& operator-=(const Direction& k) { 
            (*this)[0] -= k[0];
            (*this)[1] -= k[1];
            (*this)[2] -= k[2];
            return (*this);
         }

        // Calculate distance between positions
        static double distance(const Position& r1, const Position& r2) {
            return sqrt(distance_squared(r1, r2));
        }
        static double distance_squared(const Position& r1, const Position& r2) {
            return (r1-r2).length_squared();
        }
};

ostream& operator<<(ostream& out, const Position& v) {
    return out << "Position(" << v[0] << ", " << v[1] << ", " << v[2] << ')';
}

#endif