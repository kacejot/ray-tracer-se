#include <iostream>
#include <fstream>
#include <random>

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "hittable_list.h"
#include "constants.h"
#include "sphere.h"
#include "camera.h"
#include "utils.h"

int main() {
    auto cam = camera{};

    std::ofstream file;
    file.open("image.ppm");

    hittable_list world;

    world.add(std::make_shared<sphere>(
        glm::vec3(0,0,-1), 0.5, std::make_shared<lambertian>(glm::vec3(0.7, 0.3, 0.3))));

    world.add(std::make_shared<sphere>(
        glm::vec3(0,-100.5,-1), 100, std::make_shared<lambertian>(glm::vec3(0.8, 0.8, 0.0))));

    world.add(std::make_shared<sphere>(
        glm::vec3(1,0,-1), 0.5, std::make_shared<metal>(glm::vec3(0.8, 0.6, 0.2))));
    
    world.add(std::make_shared<sphere>(
        glm::vec3(-1,0,-1), 0.5, std::make_shared<metal>(glm::vec3(0.8, 0.8, 0.8))));

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            glm::vec3 color{};
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random()) / image_width;
                auto v = (j + random()) / image_height;
                ray r = cam.cast_ray(u, v);
				auto c = ray_color(r, world, max_depth);
				color += c;
            }
            color /= float(samples_per_pixel);
            gamma_correct(color, 0.5f);
            write_vec3(file, color);
        }
    }

    std::cout << "\nDone.\n";
}