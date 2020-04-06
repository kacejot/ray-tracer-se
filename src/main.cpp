#include <fstream>
#include <iostream>

#include <glm/geometric.hpp>

#include "hittable_list.h"
#include "sphere.h"
#include "ray.h"

void write_vec3(std::ostream &out, const glm::vec3& vec) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(vec.r) << ' '
        << static_cast<int>(vec.g) << ' '
        << static_cast<int>(vec.b) << '\n';
}

glm::vec3 linear_gradient(const glm::vec3& from, const glm::vec3& to, const ray& r) {
    glm::vec3 unit_direction = glm::normalize(r.direction);
    
    // all coordiates of unit vector are in [-1; 1]
    // scale y to [0; 1]
    auto degree = 0.5f * (unit_direction.y + 1.0f);
    return degree * from + (1.0f - degree) * to;
}

glm::vec3 sphere_gradient(const hit_record& rec) {
    return 0.5f * 255.0f * (rec.normal + glm::vec3{1, 1, 1});
}

glm::vec3 ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    return (world.hit(r, 0, std::numeric_limits<float>::infinity(), rec) ? 
        sphere_gradient(rec) :
        linear_gradient(
            glm::vec3{122, 179, 255}, // light blue
            glm::vec3{255, 255, 255}, // white
            r));
}

int main() {
    const int image_width = 200;
    const int image_height = 100;

    auto r = ray {glm::vec3{}, glm::vec3{}};

    std::ofstream file;
    file.open("image.ppm");

    glm::vec3 lower_left_corner(-2.0, -1.0, -1.0);
    glm::vec3 horizontal(4.0, 0.0, 0.0);
    glm::vec3 vertical(0.0, 2.0, 0.0);
    glm::vec3 origin(0.0, 0.0, 0.0);

    hittable_list world;
    world.add(std::make_shared<sphere>(glm::vec3{0, 0, -1}, 0.5f));
    world.add(std::make_shared<sphere>(glm::vec3{0, -100.5f, -1}, 100.0f));

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = static_cast<float>(i) / image_width;
            auto v = static_cast<float>(j) / image_height;
            
            ray r{origin, lower_left_corner + u * horizontal + v * vertical};
            glm::vec3 color = ray_color(r, world);

            write_vec3(file, color);
        }
    }

    std::cerr << "\nDone.\n";
}