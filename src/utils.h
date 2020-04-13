#pragma once

#include <algorithm>
#include <cstdlib>
#include <fstream>

#include <glm/geometric.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/vec3.hpp>

#include "hittable.h"
#include "ray.h"

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

glm::vec3 random_vec_in_hemisphere(const glm::vec3& normal) {
    glm::vec3 in_unit_sphere = random_vec_in_unit_sphere();
    if (glm::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

glm::vec3 random_unit_vector() {
    auto a = random_ranged(0, 2 * glm::pi<float>());
    auto z = random_ranged(-1, 1);
    auto r = sqrt(1 - z * z);
    return glm::vec3{r * cos(a), r * sin(a), z};
}

glm::vec3 linear_gradient(const glm::vec3& from, const glm::vec3& to, const ray& r) {
    glm::vec3 unit_direction = glm::normalize(r.direction);
    
    // all coordiates of unit vector are in [-1; 1]
    // scale y to [0; 1]
    auto degree = 0.5f * (unit_direction.y + 1.0f);
    return degree * from + (1.0f - degree) * to;
}

glm::vec3 sphere_gradient(const hit_record& rec, const hittable& world, const int depth) {
    glm::vec3 target = rec.p + rec.normal + random_vec_in_unit_sphere();
    return 0.5f * 255.0f * ray_color(ray{rec.p, target - rec.p}, world, depth - 1);
    // return 0.5f * 255.0f * (rec.normal + glm::vec3{1, 1, 1});
}

void gamma_correct(glm::vec3& color, const float gamma) {
    color.r = 255.0f * pow(color.r / 255.0f, gamma);
    color.g = 255.0f * pow(color.g / 255.0f, gamma);
    color.b = 255.0f * pow(color.b / 255.0f, gamma);
}

glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2 * glm::dot(v,n) * n;
}
