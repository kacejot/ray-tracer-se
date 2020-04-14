#include <fstream>

#include "materials/lambertian.h"
#include "materials/dielectric.h"
#include "materials/metal.h"
#include "hittable_list.h"
#include "constants.h"
#include "renderer.h"
#include "sphere.h"
#include "camera.h"

int main() {
    using materials::lambertian;
    using materials::dielectric;
    using materials::metal;

    std::ofstream file;
    file.open("image.ppm");

    hittable_list world;

    world.add(std::make_shared<sphere>(
        vec3{0.0, 0.0, -1.0}, 0.5,
        std::make_shared<lambertian>(vec3{0.7, 0.3, 0.3})));

    world.add(std::make_shared<sphere>(
        vec3{0.0, -100.5, -1.0}, 100.0,
        std::make_shared<lambertian>(vec3{0.8, 0.8, 0.0})));

    world.add(std::make_shared<sphere>(
        vec3{1.0, 0.0, -1.0}, 0.5,
        std::make_shared<metal>(vec3{0.8f, 0.8f, 0.8}, 1.0)));

    world.add(std::make_shared<sphere>(
        vec3{-1.0, 0.0, -1.0}, 0.5,
        std::make_shared<dielectric>(1.5)));

   p3_renderer{
        std::move(world),
        camera{},
        file
    }.render(IMAGE_WIDTH, IMAGE_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH);
}