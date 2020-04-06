#include <iostream>
#include <fstream>
#include <random>

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
    world.add(std::make_shared<sphere>(glm::vec3{0, 0, -1}, 0.5f));
//    world.add(std::make_shared<sphere>(glm::vec3{0.15f, 0, -1.0f}, 0.1f));
    world.add(std::make_shared<sphere>(glm::vec3{0, -100.5f, -1}, 100.0f));

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
            write_vec3(file, color);
        }
    }

    std::cout << "\nDone.\n";
}