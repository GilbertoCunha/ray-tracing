#ifndef VECTOR_H
#define VECTOR_H

#include <Eigen/Dense>
#include <iostream>
#include <math.h>
using namespace std;

/**
 * @brief Definition of the Direction class
 * 
 */
class Direction {
    private:
        Eigen::Vector3d e;
    public:
        Direction(double x, double y, double z) : e{Eigen::Vector3d(x,y,z)} {}
        Direction(const Eigen::Vector3d& v) : e{v} {}
        Direction() = default;

        // Get vector
        Eigen::Vector3d get_vector() const { return e; }

        // Indexing
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Addition
        Direction operator+(const Direction& d) const { return Direction(e + d.get_vector()); }
        Direction& operator+=(const Direction& d) {
            this->e += d.get_vector();
            return (*this);
        }
        Position operator+(const Position& d) const { return Position(e + d.get_vector()); }

        // Subtraction
        Direction operator-() const {
            return Direction(-e);
        }
        Direction operator-(const Direction& d) const { return Direction(e - d.get_vector()); }
        Direction& operator-=(const Direction& d) {
            this->e -= d.get_vector();
            return *this;
        }
        Position operator-(const Position& d) const { return Position(e - d.get_vector()); }

        // Multiplication and division
        Direction operator*(double x) const { return Direction(e * x); }
        Direction& operator*=(double x) {
            this->e *= x; 
            return *this;
        }
        Direction operator/(double x) const { return Direction(e / x); }
        Direction& operator/=(double x) {
            this->e /= x;
            return *this;
        }

        // Length operations
        double length() const { return e.norm(); }
        double length_squared() const { return e.dot(e); };
        Direction normalize() const { return (*this) / length(); }

        // Dot product with positions
        double dot(const Direction& d) const { return e.dot(d.get_vector()); }
        double dot(const Position& p) const { return e.dot(p.get_vector()); }

        // Cross product with directions
        Direction cross(const Direction& d) const { return Direction(e.cross(d.get_vector())); }

        // Angle between
        double angle(const Direction& d) const {
            return e.dot(d.get_vector()) / (length() * d.length());
        }
        double angle(const Position& d) const {
            return e.dot(d.get_vector()) / (length() * d.length());
        }
};

/**
 * @brief Definition of the Position class
 * 
 */
class Position {
    private:
        Eigen::Vector3d e;
    public:
        Position(double x, double y, double z) : e{Eigen::Vector3d(x,y,z)} {}
        Position(const Eigen::Vector3d& v) : e{v} {}
        Position() = default;

        // Get vector
        Eigen::Vector3d get_vector() const { return e; }

        // Indexing
        double operator[](int i) const { return e[i]; }
        double& operator[](int i) { return e[i]; }

        // Addition
        Position operator+(const Direction& d) const { return Position(e + d.get_vector()); }
        Position& operator+=(const Direction& d) {
            this->e += d.get_vector();
            return (*this);
        }

        // Subtraction
        Position operator-() const {
            return Position(-e);
        }
        Position operator-(const Direction& d) const { return Position(e - d.get_vector()); }
        Position& operator-=(const Direction& d) {
            this->e -= d.get_vector();
            return *this;
        }
        Direction operator-(const Position& d) const { return Direction(e - d.get_vector()); }

        // Multiplication and division
        Position operator*(double x) const { return Position(e * x); }
        Position& operator*=(double x) {
            this->e *= x; 
            return *this;
        }
        Position operator/(double x) const { return Position(e / x); }
        Position& operator/=(double x) {
            this->e /= x;
            return *this;
        }

        // Length operations
        double length() const { return e.norm(); }
        double length_squared() const { return e.dot(e); };
        Position normalize() const { return (*this) / length(); }

        // Dot products
        double dot(const Direction& d) const { return e.dot(d.get_vector()); }
        double dot(const Position& p) const { return e.dot(p.get_vector()); }

        // Cross product with directions
        Position cross(const Position& d) const { return Position(e.cross(d.get_vector())); }

        // Angle between
        double angle(const Direction& d) const {
            return e.dot(d.get_vector()) / (length() * d.length());
        }
        double angle(const Position& d) const {
            return e.dot(d.get_vector()) / (length() * d.length());
        }
};

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