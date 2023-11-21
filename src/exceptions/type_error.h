#ifndef VALUE_ERROR_H
#define VALUE_ERROR_H

#include <iostream>
using namespace std;

class TypeError: public runtime_error {
    public:
        TypeError(char const* const message) throw() : runtime_error(message) {}
};

#endif