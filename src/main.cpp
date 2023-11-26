#include <iostream>
#include <fstream>
using namespace std;

#include "rendering/camera.h"
#include "rendering/shooter.h"
#include "rendering/scene.h"
#include "objects/background.h"
#include "objects/sphere.h"
#include "materials/metal.h"
#include "materials/fuzzy_metal.h"
#include "materials/lambertian.h"
#include <optional>

/**
 * @brief Main function. Generates and renders the whole scene.
 * 
 * @return int Success of the function (0 => success, 1 => failure)
 */
int main () {

    // Global variables
    int rays_per_pixel = 50;
    int multi_scattering = 8;
    int image_height = 480;
    double fov = 0.25*M_PI;
    double aspect_ratio = 16.0 / 9.0;

    // Create camera and ray shooter
    Camera camera = Camera(
        Position(0.0, 0.0, 0.0),
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

    // Add sphere to the scene
    Lambertian material_big    = Lambertian(Color(0.8, 0.8, 0.0));
    FuzzyMetal material_left   = FuzzyMetal(Color(0.8, 0.8, 0.8), 0.1);
    Lambertian material_center = Lambertian(Color(0.7, 0.3, 0.3));
    FuzzyMetal material_right  = FuzzyMetal(Color(0.8, 0.6, 0.2), 0.2);
    Sphere sphere_big    = Sphere(Position(-100.5,  0.0,  2.0), 100.0, material_big);
    Sphere sphere_left   = Sphere(Position(   0.0, -1.0,  2.0),   0.5, material_left);
    Sphere sphere_center = Sphere(Position(   0.0,  0.0,  2.2),   0.5, material_center);
    Sphere sphere_right  = Sphere(Position(   0.0,  1.0,  2.0),   0.5, material_right);
    scene.add_object(sphere_big);
    scene.add_object(sphere_center);
    scene.add_object(sphere_left);
    scene.add_object(sphere_right);

    // Render image
    cout << "\nStarting render\n";
    scene.render(shooter, multi_scattering, "result.ppm");

    return 0;
}