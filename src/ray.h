
#include "glm/vec3.hpp"

struct ray {
    glm::vec3 orig;
    glm::vec3 dir;

    glm::vec3 origin() const    { return orig; }
    glm::vec3 direction() const { return dir; }

    glm::vec3 at(float t) const {
        return orig + t*dir;
    }
};