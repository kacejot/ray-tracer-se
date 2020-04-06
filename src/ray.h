
#pragma once

#include "glm/vec3.hpp"

struct ray {
    glm::vec3 origin;
    glm::vec3 direction;

    glm::vec3 at(float t) const {
        return origin + t * direction;
    }
};