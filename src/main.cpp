#include <fstream>

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "hittable_list.h"
#include "constants.h"
#include "renderer.h"
#include "sphere.h"
#include "camera.h"

int main() {
    using materials::lambertian;
    using materials::metal;

    std::ofstream file;
    file.open("image.ppm");

    hittable_list world;

    world.add(std::make_shared<sphere>(
        vec3{0.0f, 0.0f, -1.0f}, 0.5f,
        std::make_shared<lambertian>(vec3{0.7f, 0.3f, 0.3f})));

    world.add(std::make_shared<sphere>(
        vec3{0.0f, -100.5f, -1.0f}, 100.0f,
        std::make_shared<lambertian>(vec3{0.8f, 0.8f, 0.0f})));

    world.add(std::make_shared<sphere>(
        vec3{1.0f, 0.0f, -1.0f}, 0.5f,
        std::make_shared<metal>(vec3{0.8f, 0.6f, 0.2f})));
    
    world.add(std::make_shared<sphere>(
        vec3{-1.0f, 0.0f, -1.0f}, 0.5f,
        std::make_shared<metal>(vec3{0.8f, 0.8f, 0.8f})));

   p3_renderer{
        std::move(world),
        camera{},
        file
    }.render(IMAGE_WIDTH, IMAGE_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH);
}