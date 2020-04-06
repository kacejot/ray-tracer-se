#pragma once

#include <glm/vec3.hpp>

#include "ray.h"

class camera {
    public:
        camera() :
            origin{0.0, 0.0, 0.0},
            lower_left_corner{-2.0, -1.0, -1.0},
            horizontal{4.0, 0.0, 0.0},
            vertical{0.0, 2.0, 0.0} {}

        ray cast_ray(float u, float v) {
            return ray{origin, lower_left_corner + u * horizontal + v * vertical - origin};
        }

    public:
        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
};
