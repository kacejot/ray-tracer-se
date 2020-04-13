#pragma once

#include <glm/vec3.hpp>

#include "hittable.h"
#include "utils.h"
#include "ray.h"

struct material {
    virtual bool scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const = 0;
};
