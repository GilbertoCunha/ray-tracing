#include <iostream>
#include <fstream>
using namespace std;

#include "rendering/camera.h"
#include "rendering/shooter.h"
#include "rendering/scene.h"
#include "objects/background.h"
#include "objects/sphere.h"
#include "materials/metal.h"
#include "materials/lambertian.h"
#include <optional>

/**
 * @brief Main function. Generates and renders the whole scene.
 * 
 * @return int Success of the function (0 => success, 1 => failure)
 */
int main () {

    // Global variables
    int rays_per_pixel = 10;
    int multi_scattering = 10;
    int image_height = 720;
    double fov = 0.33*M_PI;
    double aspect_ratio = 16.0 / 9.0;

    // Create camera and ray shooter
    Camera camera = Camera(
        Position(2.0, 0.0, 0.0),
        Direction(0.0, 0.0, 1.0),
        fov=fov,
        aspect_ratio=aspect_ratio,
        image_height=image_height
    );
    AntiAliasingRayShooter shooter = AntiAliasingRayShooter(camera, rays_per_pixel);
    // GridRayShooter shooter = GridRayShooter(camera);

    // Create scene
    Background background = Background(camera);
    Scene scene = Scene(background);

    // Create materials for objects
    Metal metal = Metal();
    Lambertian lambertian = Lambertian();

    // Add sphere to the scene
    Sphere sphere1 = Sphere(
        Position(1.0, 1.0, 5.0),
        1.0,
        Color(1.0, 1.0, 1.0),
        0.999,
        lambertian
    );
    Sphere sphere2 = Sphere(
        Position(1.0, -4.0, 8.0),
        1.0,
        Color(1.0, 1.0, 1.0),
        0.6,
        lambertian
    );
    Sphere sphere3 = Sphere(
        Position(-1000.0, 0.0, 0.0),
        1000.0,
        Color(1.0, 1.0, 1.0),
        0.6,
        lambertian
    );
    scene.add_object(&sphere1);
    scene.add_object(&sphere2);
    scene.add_object(&sphere3);

    // Render image
    cout << "\nStarting render\n";
    scene.render(shooter, multi_scattering, "result.ppm");

    return 0;
}