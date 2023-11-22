#include <iostream>
#include <fstream>
using namespace std;

#include "rendering/camera.h"
#include "rendering/shooter.h"
#include "rendering/scene.h"
#include "objects/background.h"
#include "objects/sphere.h"
#include <optional>

/**
 * @brief Main function. Generates and renders the whole scene.
 * 
 * @return int Success of the function (0 => success, 1 => failure)
 */
int main () {

    // Create camera and ray shooter
    Camera camera = Camera();
    GridRayShooter shooter = GridRayShooter(camera);

    // Create scene
    Background background = Background(camera);
    Scene scene = Scene(background);

    // Add sphere to the scene
    Sphere sphere1 = Sphere(
        Position(1.0, 1.0, 5.0),
        1.5,
        Color(0.0, 1.0, 0.0)
    );
    Sphere sphere2 = Sphere(
        Position(1.0, -2.0, 8.0),
        1.5,
        Color(1.0, 0.0, 0.0)
    );
    scene.add_object(&sphere1);
    scene.add_object(&sphere2);

    // Render image
    scene.render(shooter, 20, "result.ppm");

    return 0;
}