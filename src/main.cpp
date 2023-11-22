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
    Sphere sphere = Sphere(
        Position(1.0, 0.0, 5.0),
        1.5,
        Color(1.0, 0.0, 0.0)
    );
    scene.add_object(&sphere);

    // Render image
    scene.render(shooter, 1, "result.ppm");

    return 0;
}