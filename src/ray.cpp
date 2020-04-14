#include "hit_record.h"
#include "material.h"
#include "hittable.h"
#include "utils.h"
#include "vec3.h"
#include "ray.h"

vec3 ray_color(const ray& r, const hittable& world, const int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return vec3{0, 0, 0};

    if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), rec)) {
        ray scattered;
        vec3 attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return vec3{0, 0, 0};
    }

    vec3 unit_direction = unit_vector(r.direction);
    auto t = 0.5 * (unit_direction.y + 1.0);
    return (1.0 - t) * vec3{1.0, 1.0, 1.0} + t * vec3{0.5, 0.7, 1.0};
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v,n) * n;
}
