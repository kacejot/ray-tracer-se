#include <glm/geometric.hpp>

#include "hit_record.h"
#include "ray.h"

void hit_record::set_face_normal(const ray& r, const glm::vec3& outward_normal) {
    front_face = glm::dot(r.direction, outward_normal) < 0;
    this->normal = front_face ? outward_normal :-outward_normal;
}
