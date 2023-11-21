#ifndef VALUE_ERROR_H
#define VALUE_ERROR_H

#include <iostream>
using namespace std;

class ValueError: public runtime_error {
    public:
        ValueError(char const* const message) throw() : runtime_error(message) {}
};

#endif