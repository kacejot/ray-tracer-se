#pragma once

#include <algorithm>
#include <cstdlib>
#include <fstream>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "hittable.h"
#include "ray.h"

void write_vec3(std::ostream &out, const glm::vec3& vec) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(std::clamp(vec.r, 0.0f, 255.f)) << ' '
        << static_cast<int>(std::clamp(vec.g, 0.0f, 255.f)) << ' '
        << static_cast<int>(std::clamp(vec.b, 0.0f, 255.f)) << '\n';
}

float random() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

float random_ranged(float min, float max) {
    // Returns a random real in [min,max).
    return min + (max - min) * random();
}

glm::vec3 random_vec() {
    return {random(), random(), random()};
}

glm::vec3 random_vec_ranged(float min, float max) {
    return {
        random_ranged(min, max),
        random_ranged(min, max),
        random_ranged(min, max)
    };
}

glm::vec3 random_vec_in_unit_sphere() {
    for(;;) {
        auto vec = random_vec_ranged(-1.0f, 1.0f);
        if (glm::dot(vec, vec) >= 1) {
            continue;
        }

        return vec;
    }
}

glm::vec3 linear_gradient(const glm::vec3& from, const glm::vec3& to, const ray& r) {
    glm::vec3 unit_direction = glm::normalize(r.direction);
    
    // all coordiates of unit vector are in [-1; 1]
    // scale y to [0; 1]
    auto degree = 0.5f * (unit_direction.y + 1.0f);
    return degree * from + (1.0f - degree) * to;
}

glm::vec3 ray_color(const ray& r, const hittable& world, const int depth);

glm::vec3 sphere_gradient(const hit_record& rec, const hittable& world, const int depth) {
    glm::vec3 target = rec.p + rec.normal + random_vec_in_unit_sphere();
    return 0.5f * 255.0f * ray_color(ray{rec.p, target - rec.p}, world, depth - 1);
    // return 0.5f * 255.0f * (rec.normal + glm::vec3{1, 1, 1});
}

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
        glm::vec3 target = rec.p + rec.normal + random_vec_in_unit_sphere();
        return 0.5f * ray_color(ray{rec.p, target - rec.p}, world, depth - 1);
    }

    glm::vec3 unit_direction = glm::normalize(r.direction);
    auto t = 0.5f * (unit_direction.y + 1.0f);
    return 255.0f * ((1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.5, 0.7, 1.0));
}
