#pragma once

#include "vec3.h"
#include "ray.h"

struct camera {
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    camera() :
        origin{0.0, 0.0, 0.0},
        lower_left_corner{-2.0, -1.0, -1.0},
        horizontal{4.0, 0.0, 0.0},
        vertical{0.0, 2.0, 0.0} {}

    ray cast_ray(float u, float v);
};
