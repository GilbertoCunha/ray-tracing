#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "../exceptions/value_error.h"
#include "../math/interval.h"
using namespace std;

/**
 * @brief Defines a class for a color
 * 
 */
class Color {
    protected:
        double rgb[3];
        Interval color_range = Interval(0.0, 1.0);
    
    public:

        /**
         * @brief Construct a new Color object.
         * Throws a ValueError exception whenever the channel value are
         * outside the interval [0, 1].
         * 
         * @param r 
         * @param g 
         * @param b 
         */
        Color(double r, double g, double b) : rgb{r,g,b} {
            if (!(color_range.contains(r) && color_range.contains(g) && color_range.contains(b))) {
                throw ValueError("Color channel values must lie between 0 and 1.");
            }
        }
        Color() = default;

        // Getters for channel values
        double red() const { return rgb[0]; };
        double green() const { return rgb[1]; };
        double blue() const { return rgb[2]; };

        // Multiply colors (for scattering equations)
        Color operator*(double x) const {
            return Color(
                rgb[0] * x,
                rgb[1] * x,
                rgb[2] * x
            );
        }
        Color operator*(const Color& c) const {
            return Color(
                rgb[0] * c.rgb[0],
                rgb[1] * c.rgb[1],
                rgb[2] * c.rgb[2]
            );
        }

        // Convert to string for different file formats
        string to_ppm() const {
            int red_int = red() * 255.999;
            int green_int = green() * 255.999;
            int blue_int = blue() * 255.999;
            return to_string(red_int) + " " + to_string(green_int) + " " + to_string(blue_int);
        }
};

Color sum_colors(const Color& c1, const Color& c2, double weight1=0.5, double weight2=0.5) {
    if (weight1 + weight2 != 1.0) {
        throw ValueError("Weights in color sum must add up to 1.");
    }
    return Color(
        c1.red()*weight1 + c2.red()*weight2,
        c1.green()*weight1 + c2.green()*weight2,
        c1.blue()*weight1 + c2.blue()*weight2
    );
}

ostream& operator<<(ostream& cout, const Color& c) {
    cout << "Color(";
    cout << c.red() << ", ";
    cout << c.green() << ", ";
    cout << c.blue() << ')';
    return cout;
}

#endif