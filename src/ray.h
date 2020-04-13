#pragma once

#include "vec3.h"

struct hittable;

struct ray {
    vec3 origin;
    vec3 direction;

    vec3 at(float t) const {
        return origin + t * direction;
    }
};

vec3 ray_color(const ray& r, const hittable& world, const int depth);
vec3 reflect(const vec3& v, const vec3& n);
