#pragma once

#include "glm/vec3.hpp"

struct ray {
    glm::vec3 origin;
    glm::vec3 direction;

    glm::vec3 at(float t) const {
        return origin + t * direction;
    }
};

glm::vec3 ray_color(const ray& r, const hittable& world, const int depth) {
    // hit_record rec;

    // if (depth <= 0) {
    //     return glm::vec3{0.0f, 0.0f, 0.0f};
    // }

    // return (world.hit(r, 0, std::numeric_limits<float>::infinity(), rec) ? 
    //     sphere_gradient(rec, world, depth) :
    //     linear_gradient(
    //         glm::vec3{122, 179, 255}, // light blue
    //         glm::vec3{255, 255, 255}, // white
    //         r));

    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0) {
        return glm::vec3(0,0,0);
    }

    if (world.hit(r, 0, std::numeric_limits<float>::infinity(), rec)) {
        // glm::vec3 target = rec.p + rec.normal + random_unit_vector();
        // return 0.5f * ray_color(ray{rec.p, target - rec.p}, world, depth - 1);

        ray scattered;
        glm::vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return glm::vec3{0, 0, 0};
    }

    glm::vec3 unit_direction = glm::normalize(r.direction);
    auto t = 0.5f * (unit_direction.y + 1.0f);
    return 255.0f * ((1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0));
}
