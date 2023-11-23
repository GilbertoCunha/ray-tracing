#ifndef DIRECTION_DEF_H
#define DIRECTION_DEF_H

#include <Eigen/Dense>
class Position;

/**
 * @brief Definition of the Direction class
 * 
 */
class Direction {
    public:
        Eigen::Vector3d e;
        Direction(double x, double y, double z);
        Direction(const Eigen::Vector3d& v);
        Direction();

        // Indexing
        double operator[](int i) const;
        double& operator[](int i);

        // Addition
        Direction operator+(const Direction& d) const;
        Direction& operator+=(const Direction& d);
        Position operator+(const Position& d) const;

        // Subtraction
        Direction operator-() const;
        Direction operator-(const Direction& d) const;
        Direction& operator-=(const Direction& d);
        Position operator-(const Position& d) const;

        // Multiplication and division
        Direction operator*(double x) const;
        Direction& operator*=(double x);
        Direction operator/(double x) const;
        Direction& operator/=(double x);

        // Length operations
        double length() const;
        double length_squared() const;
        Direction normalize() const;

        // Dot product with positions
        double dot(const Direction& d) const;
        double dot(const Position& p) const;

        // Cross product with directions
        Direction cross(const Direction& d) const;

        // Angle between
        double angle(const Direction& d) const;
        double angle(const Position& d) const;

        // Printing
        ostream& operator<<(ostream& cout) const;
};

ostream& operator<<(ostream& cout, const Direction& p);

#endif