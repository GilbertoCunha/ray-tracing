#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
#include "../physics/direction.h"
using namespace std;

double random_uniform(double lower, double upper) {
    double random_double = rand() / (RAND_MAX + 1.0);
    return lower + (upper - lower) * random_double;
}

Direction random_unit_vector() {
    Direction u = Direction(
        random_uniform(-1, 1),
        random_uniform(-1, 1),
        random_uniform(-1, 1)
    );
    return u.normalize();
}

#endif