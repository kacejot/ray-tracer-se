#pragma once

#include "material.h"
#include "vec3.h"

namespace materials {
    struct metal : public material {
        vec3 albedo;
        double fuzz;

        metal(const vec3& albedo, double fuzz) : albedo{albedo}, fuzz{fuzz} {}

        bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;
    };
}
