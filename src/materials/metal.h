#pragma once

#include "material.h"

class metal : public material {
    public:
        metal(const glm::vec3& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered
        ) const override {
            glm::vec3 reflected = reflect(r_in.direction, rec.normal);
            scattered = ray{rec.p, reflected};
            attenuation = albedo;
            return (glm::dot(scattered.direction, rec.normal) > 0);
        }

    public:
        glm::vec3 albedo;
};
