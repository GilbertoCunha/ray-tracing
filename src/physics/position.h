#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include "position_def.h"
#include "direction_def.h"
using namespace std;

// Constructors
Position::Position(double x, double y, double z) : e{Eigen::Vector3d(x,y,z)} {}
Position::Position(const Eigen::Vector3d& v) : e{v} {}
Position::Position() = default;

// Indexing
double Position::operator[](int i) const { return e[i]; }
double& Position::operator[](int i) { return e[i]; }

// Addition
Position Position::operator+(const Direction& d) const { return Position(e + d.e); }
Position& Position::operator+=(const Direction& d) {
    this->e += d.e;
    return (*this);
}

// Subtraction
Position Position::operator-() const { return Position(-e); }
Position Position::operator-(const Direction& d) const { return Position(e - d.e); }
Position& Position::operator-=(const Direction& d) {
    this->e -= d.e;
    return *this;
}
Direction Position::operator-(const Position& d) const { return Direction(e - d.e); }

// Multiplication and division
Position Position::operator*(double x) const { return Position(e * x); }
Position& Position::operator*=(double x) {
    this->e *= x; 
    return *this;
}
Position Position::operator/(double x) const { return Position(e / x); }
Position& Position::operator/=(double x) {
    this->e /= x;
    return *this;
}

// Length operations
double Position::length() const { return e.norm(); }
double Position::length_squared() const { return e.dot(e); };
Position Position::normalize() const { return (*this) / length(); }

// Dot products
double Position::dot(const Direction& d) const { return e.dot(d.e); }
double Position::dot(const Position& p) const { return e.dot(p.e); }

// Cross product with directions
Position Position::cross(const Position& d) const { return Position(e.cross(d.e)); }

// Angle between
double Position::angle(const Direction& d) const { return e.dot(d.e) / (length() * d.length()); }
double Position::angle(const Position& d) const { return e.dot(d.e) / (length() * d.length()); }

// Printing
ostream& Position::operator<<(ostream& cout) const {
    cout << "Position(";
    cout << e[0] << ", ";
    cout << e[1] << ", ";
    cout << e[2] << ')';
    return cout;
}
ostream& operator<<(ostream& cout, const Position& p) { return cout << p; }

#endif