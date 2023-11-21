# Ray tracing engine

This is a side project for a `ray-tracing` engine.

I have a love for physics, and visual graphics are just so satisfying to program.

This is a project for me to do and share what I love. I hope you find it interesting and useful!

I am also thoroughly documenting everything thoroughly, so that both you and I can learn along the way.

Hope you enjoy this almost as much as I do!


# TODO

## Functionality roadmap:

1. ~~Camera~~
2. ~~Shooting rays~~
3. ~~Background~~
4. ~~Color sphere~~
5. ~~Floor~~ (made it embedded into background)
6. Improve Documentation
7. Anti aliasing (shoot multiple random rays)
8. Diffuse reflection
9. Metallic reflection
10. Refraction


## Quality improvements

1. Shift logic from header `.h` files to `.cpp` files
2. Write `unit` tests
3. Create an `Orientation` for the camera
4. ~~Better abstraction in shooting the rays for the camera:~~
    - Create `Camera` object just with its properties
    - Create `Shooter` object to define the rays to trace
    - Create `Scene` object that holds the whole scene together:
        - `Camera`
        - `Shooter`
        - `Background` (hittable `Sphere`)
        - `Spheres`
        - `Floor`
5. Separate concerns between `Object` and `Material`:
    - A `Material` should be described by a **BRDF** (bi-directional reflectance distribution function).
    This BRDF describes how likely a pair of incoming and outgoing light rays are.
    - An `ScatterSampler` object should define how to choose an outgoing ray given an incoming ray and a `Material` (defined by a **BRDF**).
    - An `Object` should be instanciated with a `Material` and a `ScatterSampler`. The `Object`'s concern is now only **geometrical**: calculate ray intersections.
    - The `Color` of the outgoing ray is calculated using multiplication.