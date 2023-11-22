#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>
using namespace std;

double random_uniform(double lower, double upper) {
    double random_double = rand() / (RAND_MAX + 1.0);
    return lower + (upper - lower) * random_double;
}

#endif