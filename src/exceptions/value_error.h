#ifndef VALUE_ERROR_H
#define VALUE_ERROR_H

#include <iostream>
#include <cstring>
#include <exception>
using namespace std;


class ValueError: public exception {
    private:
        const char* description;
    
    public:

        ValueError(string description) : description{description.c_str()} {};

        virtual const char* what() const throw() {
            return description;
        }
};


#endif