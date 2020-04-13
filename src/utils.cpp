#include <algorithm>
#include <cstdlib>

#include "hit_record.h"
#include "utils.h"

float random() {
    return rand() / (RAND_MAX + 1.0f);
}

float random_ranged(float min, float max) {  
    return min + (max - min) * random();
}

vec3 random_vec() {
    return {random(), random(), random()};
}

vec3 random_vec_ranged(float min, float max) {
    return {
        random_ranged(min, max),
        random_ranged(min, max),
        random_ranged(min, max)
    };
}

vec3 random_vec_in_unit_sphere() {
    for(;;) {
        auto vec = random_vec_ranged(-1.0f, 1.0f);
        if (glm::dot(vec, vec) >= 1) {
            continue;
        }

        return vec;
    }
}

vec3 random_vec_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_vec_in_unit_sphere();
    if (glm::dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 random_unit_vector() {
    auto a = random_ranged(0, 2 * glm::pi<float>());
    auto z = random_ranged(-1, 1);
    auto r = sqrt(1 - z * z);
    return vec3{r * cos(a), r * sin(a), z};
}

vec3 linear_gradient(const vec3& from, const vec3& to, const ray& r) {
    vec3 unit_direction = glm::normalize(r.direction);
    
    // all coordiates of unit vector are in [-1; 1]
    // scale y to [0; 1]
    auto degree = 0.5f * (unit_direction.y + 1.0f);
    return degree * from + (1.0f - degree) * to;
}

vec3 sphere_gradient(const hit_record& rec, const hittable& world, const int depth) {
    vec3 target = rec.p + rec.normal + random_vec_in_unit_sphere();
    return 0.5f * ray_color(ray{rec.p, target - rec.p}, world, depth - 1);
}

void gamma_correct(vec3& color, const float gamma) {
    color.r = pow(color.r, gamma);
    color.g = pow(color.g, gamma);
    color.b = pow(color.b, gamma);
}

