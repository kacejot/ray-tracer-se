#pragma once

#include "material.h"

class lambertian : public material {
    public:
        lambertian(const  glm::vec3& a) : albedo(a) {}

        bool scatter(
            const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered
        ) const override {
            glm::vec3 scatter_direction = rec.normal + random_unit_vector();
            scattered = ray{rec.p, scatter_direction};
            attenuation = albedo;
            return true;
        }

    public:
        glm::vec3 albedo;
};