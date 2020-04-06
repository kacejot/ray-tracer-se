#include "ray.h"

#include <fstream>
#include <iostream>
#include <glm/geometric.hpp>

void write_vec3(std::ostream &out, const glm::vec3& vec) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(vec.r) << ' '
        << static_cast<int>(vec.g) << ' '
        << static_cast<int>(vec.b) << '\n';
}

glm::vec3 linear_gradient(const glm::vec3& from, const glm::vec3& to, const ray& r) {
    glm::vec3 unit_direction = glm::normalize(r.direction());
    
    // all coordiates of unit vector are in [-1; 1]
    // scale y to [0; 1]
    auto degree = 0.5f * (unit_direction.y + 1.0f);
    return degree * from + (1.f - degree) * to;
}

glm::vec3 sphere_gradient(const float hit_point, const ray& r) {
        auto N = glm::normalize(r.at(hit_point) - glm::vec3{0, 0, -1});
        return 0.5f * 255.0f * glm::vec3{N.x + 1, N.y + 1, N.z + 1};
}

double hit_sphere(const glm::vec3& center, double radius, const ray& r) {
    glm::vec3 oc = r.origin() - center;
    auto a = glm::dot(r.direction(), r.direction());
    auto b = 2.0 * glm::dot(oc, r.direction());
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

glm::vec3 ray_color(const ray& r) {
    auto t = hit_sphere(glm::vec3{0, 0, -1}, 0.5, r);
    return (t > 0 ? 
        sphere_gradient(t, r) :
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

    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = static_cast<float>(i) / image_width;
            auto v = static_cast<float>(j) / image_height;
            
            ray r{origin, lower_left_corner + u*horizontal + v*vertical};
            glm::vec3 color = ray_color(r);

            write_vec3(file, color);
        }
    }

    std::cerr << "\nDone.\n";
}