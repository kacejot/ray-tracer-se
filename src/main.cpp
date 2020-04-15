#include <fstream>

#include "materials/lambertian.h"
#include "materials/dielectric.h"
#include "materials/metal.h"
#include "hittable_list.h"
#include "constants.h"
#include "renderer.h"
#include "sphere.h"
#include "camera.h"
#include "utils.h"

using materials::lambertian;
using materials::dielectric;
using materials::metal;

hittable_list random_scene() {
    hittable_list world;

    world.add(std::make_shared<sphere>(
        vec3{0.0, -1000.0, 0.0}, 1000.0,
        std::make_shared<lambertian>(vec3{0.5, 0.5, 0.5})));

    int i = 1;
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            vec3 center{a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()};
            if ((center - vec3{4, 0.2, 0}).length() > 0.9) {
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_vec() * random_vec();
                    world.add(std::make_shared<sphere>(
                        center, 0.2,
                        std::make_shared<lambertian>(albedo)));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_vec_ranged(0.5, 1.0);
                    auto fuzz = random_double_ranged(0.0, 0.5);
                    world.add(std::make_shared<sphere>(
                        center, 0.2,
                        std::make_shared<metal>(albedo, fuzz)));
                } else {
                    // glass
                    world.add(std::make_shared<sphere>(
                        center, 0.2,
                        std::make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    world.add(std::make_shared<sphere>(
        vec3{0.0, 1.0, 0.0}, 1.0, 
        std::make_shared<dielectric>(1.5)));

    world.add(std::make_shared<sphere>(
        vec3{-4.0, 1.0, 0.0}, 1.0,
        std::make_shared<lambertian>(vec3{0.4, 0.2, 0.1})));

    world.add(std::make_shared<sphere>(
        vec3{4, 1, 0}, 1.0,
        std::make_shared<metal>(vec3{0.7, 0.6, 0.5}, 0.0)));

    return world;
}


int main() {
    std::ofstream file;
    file.open("image.ppm");

    const auto world = random_scene();
    const auto look_from = vec3{13.0, 2.0, 3.0};
    const auto look_at = vec3{0.0, 0.0, 0.0};
    const auto vup = vec3{0.0, 1.0, 0.0};
    const auto fov = 20;
    const auto dist_to_focus = 10.0;
    const auto aperture = 0.1;

    p3_renderer{
        std::move(world),
        camera{look_from, look_at, vup, fov, ASPECT_RATIO, aperture, dist_to_focus},
        file
    }.render(IMAGE_WIDTH, IMAGE_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH);
}