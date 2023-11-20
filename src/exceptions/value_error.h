#ifndef VALUE_ERROR_H
#define VALUE_ERROR_H

#include <iostream>
#include <cstring>
using namespace std;


class ValueError: public runtime_error {
    string message;
    public:
        ValueError(char const* const message) throw() : runtime_error(message), message{message} {}
        const char* what() const throw() override{
            return message.c_str();
        }
};


#endif