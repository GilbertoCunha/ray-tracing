#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <math.h>
using namespace std;

/**
 * @brief Definition of the Direction class
 * 
 */
class Direction {
    private:
        double e[3];
    public:
        Direction(double x, double y, double z) : e{x,y,z} {}
        Direction() = default;

        // Indexing operations
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Translation operations
        Direction operator+(const Direction& u) const {
            return Direction(
                e[0] + u[0],
                e[1] + u[1],
                e[2] + u[2]
            );
        }
        Direction& operator+=(const Direction& u) {
            e[0] += u[0];
            e[1] += u[1];
            e[2] += u[2];
            return (*this);
        }
        Direction operator-() {
            return Direction(-e[0], -e[1], -e[2]);
        }
        Direction operator-(const Direction& u) const {
            return Direction(
                e[0] - u[0],
                e[1] - u[1],
                e[2] - u[2]
            );
        }
        Direction& operator-=(const Direction& u) {
            e[0] -= u[0];
            e[1] -= u[1];
            e[2] -= u[2];
            return (*this);
        }

        // Scaling operations
        Direction operator*(double x) const {
            return Direction(
                e[0] * x,
                e[1] * x,
                e[2] * x
            );
        }
        Direction& operator*=(double x) {
            e[0] *= x;
            e[1] *= x;
            e[2] *= x;
            return (*this);
        }
        Direction operator/(double x) const {
            return Direction(
                e[0] / x,
                e[1] / x,
                e[2] / x
            );
        }
        Direction& operator/=(double x) {
            e[0] /= x;
            e[1] /= x;
            e[2] /= x;
            return (*this);
        }

        // Length operations
        double length() const;
        double length_squared() const;

        // Normalization
        Direction normalize() const { return (*this) / (*this).length(); }
};

/**
 * @brief Definition of the Position class
 * 
 */
class Position {
    private:
        double e[3];
    public:
        Position(double x, double y, double z) : e{x,y,z} {}
        Position() = default;

        // Indexing operations
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Subtraction
        // Position - Position = Direction
        Position operator-() const {
            return Position(-e[0], -e[1], -e[2]);
        }
        Direction operator-(const Position& p) const {
            return Direction(
                e[0]-p[0],
                e[1]-p[1],
                e[2]-p[2]
            );
        }

        // Translation operations
        Position operator+(const Direction& u) const {
            return Position(
                e[0]+u[0],
                e[1]+u[1],
                e[2]+u[2]
            );
        }
        Position operator-(const Direction& u) const {
            return Position(
                e[0]-u[0],
                e[1]-u[1],
                e[2]-u[2]
            );
        }

        // Scaling operations
        Position operator*(double x) const {
            return Position(
                e[0]*x,
                e[1]*x,
                e[2]*x
            );
        }
        Position& operator*=(double x) {
            e[0] *= x;
            e[1] *= x;
            e[2] *= x;
            return (*this);
        }
        Position operator/(double x) const {
            return Position(
                e[0]/x,
                e[1]/x,
                e[2]/x
            );
        }
        Position& operator/=(double x) {
            e[0] /= x;
            e[1] /= x;
            e[2] /= x;
            return (*this);
        }

        double length() const;
        double length_squared() const;
};


// Dot products
double dot(const Position& p, const Position& q) {
    return p[0]*q[0] + p[1]*q[1] * p[2]*q[2];
}
double dot(const Direction& u, const Direction& v) {
    return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}
double dot(const Position& p, const Direction& u) {
    return p[0]*u[0] + p[1]*u[1] * p[2]*u[2];
}
double dot(const Direction& u, const Position& p) {
    return p[0]*u[0] + p[1]*u[1] * p[2]*u[2];
}

// Length operations
double Position::length() const { return sqrt(length_squared()); }
double Position::length_squared() const { return dot((*this), (*this)); }
double Direction::length() const { return sqrt(length_squared()); }
double Direction::length_squared() const { return dot(*this, *this); }

// Cross products
Position cross(const Position& p, const Position& q) {
    return Position(
        p[1]*q[2] - p[2]*q[1],
        p[2]*q[0] - p[0]*q[2],
        p[0]*q[1] - p[1]*q[0]
    );
}
Direction cross(const Direction& u, const Direction& v) {
    return Direction(
        u[1]*v[2]-u[2]*v[1],
        u[2]*v[0]-u[0]*v[2],
        u[0]*v[1]-u[1]*v[0]
    );
}

// Printing
ostream& operator<<(ostream& cout, const Position& p) {
    cout << "Position(";
    cout << p[0] << ", ";
    cout << p[1] << ", ";
    cout << p[2] << ')';
    return cout;
}
ostream& operator<<(ostream& cout, const Direction& u) {
    cout << "Direction(";
    cout << u[0] << ", ";
    cout << u[1] << ", ";
    cout << u[2] << ')';
    return cout;
}

#endif