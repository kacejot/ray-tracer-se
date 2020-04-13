#pragma once

#include <memory>

#include "hittable.h"
#include "vec3.h"

struct material;

struct sphere: public hittable {
    std::shared_ptr<material> mat_ptr;
    vec3 center;
    float radius;

    sphere(const vec3& center, const float radius, std::shared_ptr<material> m) : center(center), radius(radius), mat_ptr(m) {}

    bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
};


