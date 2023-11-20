#ifndef INTERVAL_H
#define INTERVAL_H

#include "../exceptions/value_error.h"
#include <math.h>
#include <limits>
using namespace std;

/**
 * @brief Defines a real-valued interval.
 * 
 */
class Interval {

    private:
        double interval[2]; // Represents the lower and upper values
        bool open[2]; // Represents whether the interval is open or closed in both ends
        double inf = numeric_limits<double>::infinity(); // Represents infinity
    
    public:

        /**
         * @brief Construct a new Interval object.
         * Throws an exception when an interval defined with -inf or +inf is not open ended.
         * Intervals with interval[0] > interval[1] are used to represent empty intervals.
         * 
         * @param interval 
         * @param open 
         */
        Interval(double low, double up, bool low_open=false, bool up_open=false) {
            if ((abs(low) == inf && !low_open) || (abs(up) == inf && !up_open)) {
                throw ValueError("And interval with infinity must be open.");
            } else {
                (*this).interval[0] = low;
                (*this).interval[1] = up;
                (*this).open[0] = low_open;
                (*this).open[1] = up_open;
            }
        };

        /**
         * @brief Checks whether the interval contains a value
         * 
         * @param value The value to check if it belongs to the interval
         * @return bool Interval contains value
         */
        bool contains(double value) const {
            bool lower_ok = (open[0] && interval[0] < value) || (!open[0] && interval[0] <= value);
            bool upper_ok = (open[1] && value < interval[1]) || (!open[1] && value <= interval[1]);
            return lower_ok && upper_ok;
        }

};

#endif
