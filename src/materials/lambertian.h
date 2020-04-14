#pragma once

#include "material.h"
#include "vec3.h"

namespace materials {
    struct lambertian : public material {
        vec3 albedo;
        
        lambertian(const  vec3& a) : albedo(a) {}

        bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;
    };
}
