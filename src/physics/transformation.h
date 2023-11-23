#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include <Eigen/Dense>
#include "direction.h"

class Row : public Eigen::Vector3d {
    public:
        Row(double x, double y, double z) : Eigen::Vector3d(x, y, z) {}
        Row(const Eigen::Vector3d& v) : Eigen::Vector3d(v) {}
        Row() = default;
};

class Column : public Eigen::Vector3d {
    public:
        Column(double x, double y, double z) : Eigen::Vector3d(x, y, z) {}
        Column(const Eigen::Vector3d& v) : Eigen::Vector3d(v) {}
        Column() = default;
};

class Transformation {
    private:
        Eigen::Matrix3d m;
    public:
        Transformation(const Row& r1, const Row& r2, const Row& r3) { 
            m.row(0) = r1;
            m.row(1) = r2;
            m.row(2) = r3;
        }
        Transformation(const Column& r1, const Column& r2, const Column& r3) { m << r1, r2, r3; }
        Transformation(const Eigen::Matrix3d matrix) : m{matrix} {}
        Transformation() = default;

        // Get matrix
        Eigen::Matrix3d get_matrix() const { return m; }

        // Dot product with directions
        Direction operator*(const Direction& d) const { return Direction(m * d.e); }
        Position operator*(const Position& d) const { return Position(m * d.e); }
        Transformation operator*(const Transformation& t) const { return Transformation(m * t.get_matrix()); }
};

/**
 * @brief A rotation matrix given the axis of rotation and the angle.
 * Equations can be found in the wikipedia page:
 * https://en.wikipedia.org/wiki/Rotation_matrix
 * 
 */
class Rotation : public Transformation {
    public:
        Rotation(const Direction& axis, double angle) : Transformation{
            Row(
                cos(angle) + axis[0]*axis[0]*(1-cos(angle)),
                axis[0]*axis[1]*(1-cos(angle)) - axis[2]*sin(angle),
                axis[0]*axis[2]*(1-cos(angle)) + axis[1]*sin(angle)
            ),
            Row(
                axis[1]*axis[0]*(1-cos(angle)) + axis[2]*sin(angle),
                cos(angle) + axis[1]*axis[1]*(1-cos(angle)),
                axis[1]*axis[2]*(1-cos(angle)) - axis[0]*sin(angle)
            ),
            Row(
                axis[2]*axis[0]*(1-cos(angle)) - axis[1]*sin(angle),
                axis[2]*axis[1]*(1-cos(angle)) + axis[0]*sin(angle),
                cos(angle) + axis[2]*axis[2]*(1-cos(angle))
            )
        } {}
        Rotation() = default;
};

#endif