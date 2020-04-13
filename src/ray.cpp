#include <glm/geometric.hpp>

#include "hit_record.h"
#include "material.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"
#include "ray.h"

vec3 ray_color(const ray& r, const hittable& world, const int depth) {
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (0 == depth) {
        return vec3{0.0f, 0.0f, 0.0f};
    }
        
    hit_record rec;
    if (world.hit(r, 0.0f, std::numeric_limits<float>::infinity(), rec)) {
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth - 1);
        }
            
        return vec3{0.0f, 0.0f, 0.0f};
    }

    return linear_gradient(
        vec3{1.0f, 1.0f, 1.0f},
        vec3{0.5f, 0.7f, 1.0f},
        r);
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * glm::dot(v,n) * n;
}
