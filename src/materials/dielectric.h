#pragma once

#include "material.h"
#include "vec3.h"

namespace materials {
    struct dielectric : public material {
        double ref_idx;
        
        dielectric(double ref_idx) : ref_idx{ref_idx} {}

        bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;
    };
}
