#ifndef DIRECTION_H
#define DIRECTION_H

#include <iostream>
#include "direction_def.h"
#include "position_def.h"
using namespace std;

// Constructors
Direction::Direction(double x, double y, double z) : e{Eigen::Vector3d(x,y,z)} {}
Direction::Direction(const Eigen::Vector3d& v) : e{v} {}
Direction::Direction() = default;

// Indexing
double Direction::operator[](int i) const { return e[i]; }
double& Direction::operator[](int i) { return e[i]; }

// Addition
Direction Direction::operator+(const Direction& d) const { return Direction(e + d.e); }
Direction& Direction::operator+=(const Direction& d) {
    this->e += d.e;
    return (*this);
}
Position Direction::operator+(const Position& d) const { return Position(e + d.e); }

// Subtraction
Direction Direction::operator-() const { return Direction(-e); }
Direction Direction::operator-(const Direction& d) const { return Direction(e - d.e); }
Direction& Direction::operator-=(const Direction& d) {
    this->e -= d.e;
    return *this;
}
Position Direction::operator-(const Position& d) const { return Position(e - d.e); }

// Multiplication and division
Direction Direction::operator*(double x) const { return Direction(e * x); }
Direction& Direction::operator*=(double x) {
    this->e *= x; 
    return *this;
}
Direction Direction::operator/(double x) const { return Direction(e / x); }
Direction& Direction::operator/=(double x) {
    this->e /= x;
    return *this;
}

// Length operations
double Direction::length() const { return e.norm(); }
double Direction::length_squared() const { return e.dot(e); };
Direction Direction::normalize() const { return (*this) / length(); }

// Dot product with positions
double Direction::dot(const Direction& d) const { return e.dot(d.e); }
double Direction::dot(const Position& p) const { return e.dot(p.e); }

// Cross product with directions
Direction Direction::cross(const Direction& d) const { return Direction(e.cross(d.e)); }

// Angle between
double Direction::angle(const Direction& d) const { return e.dot(d.e) / (length() * d.length()); }
double Direction::angle(const Position& d) const { return e.dot(d.e) / (length() * d.length()); }

// Printing
ostream& Direction::operator<<(ostream& cout) const {
    cout << "Direction(";
    cout << e[0] << ", ";
    cout << e[1] << ", ";
    cout << e[2] << ')';
    return cout;
}
ostream& operator<<(ostream& cout, const Direction& d) { return cout << d; }

#endif