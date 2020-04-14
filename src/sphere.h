#pragma once

#include <memory>

#include "hittable.h"
#include "vec3.h"

struct material;

struct sphere: public hittable {
    std::shared_ptr<material> mat_ptr;
    vec3 center;
    double radius;

    sphere(const vec3& center, const double radius, std::shared_ptr<material> m) : center(center), radius(radius), mat_ptr(m) {}

    bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;
};


