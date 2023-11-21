#include <iostream>
#include <fstream>
using namespace std;

#include "rendering/camera.h"
#include "rendering/shooter.h"
#include "rendering/scene.h"
#include "objects/background.h"
#include <optional>

/**
 * @brief Main function. Generates and renders the whole scene.
 * 
 * @return int Success of the function (0 => success, 1 => failure)
 */
int main () {

    /*
    // Create Ray and Sphere
    Ray ray = Ray(
        Position(0.0, 0.0, -2.0),
        Direction(0.0, 0.0, 1.0),
        Color(1.0, 1.0, 1.0)
    );
    Sphere sphere = Sphere(
        Position(0.0, 0.0, 0.0),
        1.0
    );
    cout << '\n';
    cout << "###################" << '\n';
    cout << "# CREATED OBJECTS #" << '\n';
    cout << "###################" << '\n';
    cout << ray << '\n';
    cout << sphere << '\n';

    optional<Position> intersection = sphere.intersection_position(ray);
    cout << '\n';
    cout << "################" << '\n';
    cout << "# INTERSECTION #" << '\n';
    cout << "################" << '\n';
    if (intersection.has_value()) {
        cout << intersection.value();
    } else {
        cout << "No intersection found.";
    }
    cout << '\n';

    // Debug dot product
    Direction x = Direction(1.0, 0.0, 0.0);
    Direction y = Direction(0.0, 1.0, 0.0);
    Direction z = Direction(0.0, 0.0, 1.0);
    cout << '\n';
    cout << "###############" << '\n';
    cout << "# DOT PRODUCT #" << '\n';
    cout << "###############" << '\n';
    cout << "x.y: " << dot(x,y) << '\n';
    cout << "x.z: " << dot(x,z) << '\n';
    cout << "x.z: " << dot(x,z) << '\n';
    cout << "(x+y).y: " << dot(x+y,y) << '\n';

    // Create rotation matrix
    Rotation r = Rotation(
        Direction(0.0, 0.0, 1.0),
        -0.25 * M_PI
    );
    Direction d = Direction(0.0, 1.0, 0.0);
    cout << '\n';
    cout << "#####################" << '\n';
    cout << "# INITIAL DIRECTION #" << '\n';
    cout << "#####################" << '\n';
    cout << d << '\n';
    cout << '\n';
    cout << "##################" << '\n';
    cout << "# AFTER ROTATION #" << '\n';
    cout << "##################" << '\n';
    cout << dot(r, d) << '\n';
    */

    // Create camera and ray shooter
    Camera camera = Camera();
    GridRayShooter shooter = GridRayShooter(camera);

    // Create scene
    Background background = Background(Position(0.0, 0.0, 0.0), 12.0);
    Scene scene = Scene(&background);

    // Render image
    scene.render(shooter, 10, "result.ppm");

    return 0;
}