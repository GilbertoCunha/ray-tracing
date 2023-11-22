#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "../exceptions/value_error.h"
#include "../math/interval.h"
using namespace std;

double clip(double channel) {
    return min(max(channel, 0.0), 1.0);
}

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
                clip(rgb[0] * x),
                clip(rgb[1] * x),
                clip(rgb[2] * x)
            );
        }
        Color operator*(const Color& c) const {
            return Color(
                clip(rgb[0] * c.rgb[0]),
                clip(rgb[1] * c.rgb[1]),
                clip(rgb[2] * c.rgb[2])
            );
        }

        // Convert image to different file formats
        string to_ppm() const;
};

Color sum_colors(const Color& c1, const Color& c2, double weight1=0.5, double weight2=0.5) {
    if (weight1 + weight2 != 1.0) {
        throw ValueError("Weights in color sum must add up to 1.");
    }
    return Color(
        clip(c1.red()*weight1 + c2.red()*weight2),
        clip(c1.green()*weight1 + c2.green()*weight2),
        clip(c1.blue()*weight1 + c2.blue()*weight2)
    );
}

ostream& operator<<(ostream& cout, const Color& c) {
    cout << "Color(";
    cout << c.red() << ", ";
    cout << c.green() << ", ";
    cout << c.blue() << ')';
    return cout;
}

Color gamma_correction(const Color& c) {
    return Color(
        clip(sqrt(c.red())),
        clip(sqrt(c.green())),
        clip(sqrt(c.blue()))
    );
}

// Convert to string for ppm images
string Color::to_ppm() const {
    Color corrected = gamma_correction(*this);
    int red_int = corrected.red() * 255.999;
    int green_int = corrected.green() * 255.999;
    int blue_int = corrected.blue() * 255.999;
    return to_string(red_int) + " " + to_string(green_int) + " " + to_string(blue_int);
}

#endif