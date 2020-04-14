#include "materials/metal.h"
#include "hit_record.h"
#include "utils.h"

bool materials::metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
    vec3 reflected = reflect(r_in.direction, rec.normal);
    scattered = ray{rec.p, reflected + fuzz * random_vec_in_unit_sphere()};
    attenuation = albedo;
    return (dot(scattered.direction, rec.normal) > 0);
}
