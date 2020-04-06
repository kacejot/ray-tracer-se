#pragma once

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include "ray.h"

struct hit_record {
    float t;
    glm::vec3 p;
    glm::vec3 normal;
    bool front_face;

    void set_face_normal(const ray& r, const glm::vec3& outward_normal) {
        front_face = glm::dot(r.direction, outward_normal) < 0;
        this->normal = front_face ? outward_normal :-outward_normal;
    }
};

struct hittable {
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
