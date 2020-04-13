#pragma once

#include <memory>

#include "vec3.h"

struct material;
struct ray;

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
    bool front_face;
    std::shared_ptr<material> mat_ptr;

    void set_face_normal(const ray& r, const vec3& outward_normal);
};