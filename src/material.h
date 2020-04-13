#pragma once

#include "vec3.h"

struct hit_record;
struct ray;

struct material {
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};
