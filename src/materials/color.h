#ifndef COLOR_H
#define COLOR_H

#include <Eigen/Dense>
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
        Eigen::Vector3d rgb;
        Interval color_range = Interval(0.0, 1.0);
        Color(const Eigen::Vector3d& v) : rgb{v} {
            if (!(color_range.contains(v[0]) && color_range.contains(v[1]) && color_range.contains(v[2]))) {
                throw ValueError("Color channel values must lie between 0 and 1.");
            }
        }
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
        Color(double r, double g, double b) : rgb{Eigen::Vector3d(r,g,b)} {
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
        Color operator*(double x) const { return Color(rgb * x); }
        Color operator*(const Color& c) const { return Color(rgb[0]*c.rgb[0], rgb[1]*c.rgb[1], rgb[2]*c.rgb[2]); }
        Color mix(const Color& c2, double w1=0.5, double w2=0.5) {
            if (w1 + w2 != 1.0) throw ValueError("Weights in color sum must add up to 1.");
            return Color(rgb * w1 + c2.rgb * w2);
        }

        Color gamma_correction() const { return Color(sqrt(rgb[0]), sqrt(rgb[1]), sqrt(rgb[2])); }

        // Convert image to different file formats
        string to_ppm() const {
            Color corrected = gamma_correction();
            int red_int = corrected.red() * 255.999;
            int green_int = corrected.green() * 255.999;
            int blue_int = corrected.blue() * 255.999;
            return to_string(red_int) + " " + to_string(green_int) + " " + to_string(blue_int);
        };
};

ostream& operator<<(ostream& cout, const Color& c) {
        cout << "Color(";
        cout << c.red() << ", ";
        cout << c.green() << ", ";
        cout << c.blue() << ')';
        return cout;
    }

#endif