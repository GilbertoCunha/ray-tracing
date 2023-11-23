#ifndef POSITION_DEF_H
#define POSITION_DEF_G

#include <Eigen/Dense>
class Direction;

class Position {
    public:
        Eigen::Vector3d e;
        Position(double x, double y, double z);
        Position(const Eigen::Vector3d& v);
        Position();

        // Indexing
        double operator[](int i) const;
        double& operator[](int i);

        // Addition
        Position operator+(const Direction& d) const;
        Position& operator+=(const Direction& d);

        // Subtraction
        Position operator-() const;
        Position operator-(const Direction& d) const;
        Position& operator-=(const Direction& d);
        Direction operator-(const Position& d) const;

        // Multiplication and division
        Position operator*(double x) const;
        Position& operator*=(double x);
        Position operator/(double x) const;
        Position& operator/=(double x);

        // Length operations
        double length() const;
        double length_squared() const;
        Position normalize() const;

        // Dot products
        double dot(const Direction& d) const;
        double dot(const Position& p) const;

        // Cross product with directions
        Position cross(const Position& d) const;

        // Angle between
        double angle(const Direction& d) const;
        double angle(const Position& d) const;

        // Printing
        ostream& operator<<(ostream& cout) const;
};

ostream& operator<<(ostream& cout, const Position& p);

#endif