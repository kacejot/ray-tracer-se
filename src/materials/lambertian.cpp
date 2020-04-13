#include "materials/lambertian.h"
#include "hit_record.h"
#include "utils.h"

bool materials::lambertian::scatter(const ray& r_in, const hit_record& rec, glm::vec3& attenuation, ray& scattered) const {
    glm::vec3 scatter_direction = rec.normal + random_unit_vector();
    scattered = ray{rec.p, scatter_direction};
    attenuation = albedo;
    return true;
}
