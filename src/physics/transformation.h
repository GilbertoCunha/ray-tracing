#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "vector.h"

using Row = Direction;

class Transformation {
    private:
        Row row[3];
    public:
        Transformation(Row r1, Row r2, Row r3) {
            row[0] = r1;
            row[1] = r2;
            row[2] = r3;
        }
        Transformation() = default;

        // Indexing operators
        Row operator[](int i) const { return row[i]; }
        Row& operator[](int i) { return row[i]; }
};

// Apply transformations to vectors and positions
Direction dot(Transformation& t, Direction& u) {
    return Direction(
        dot(t[0], u),
        dot(t[1], u),
        dot(t[2], u)
    );
}
Position dot(Transformation& t, Position& u) {
    return Position(
        dot(t[0], u),
        dot(t[1], u),
        dot(t[2], u)
    );
}

/**
 * @brief A rotation matrix given the axis of rotation and the angle.
 * Equations can be found in the wikipedia page:
 * https://en.wikipedia.org/wiki/Rotation_matrix
 * 
 */
class Rotation : public Transformation {
    public:
        Rotation(Direction axis, double angle) : Transformation{
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