#include "dielectric.h"
#include "hit_record.h"
#include "utils.h"
#include "ray.h"

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
    auto cos_theta = dot(-uv, n);
    vec3 r_out_parallel =  etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_perp = -sqrt(1.0 - r_out_parallel.length_squared()) * n;
    return r_out_parallel + r_out_perp;
}

double schlick(double cosine, double ref_idx) {
    auto r0 = (1 - ref_idx) / (1+  ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool materials::dielectric::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
    attenuation = vec3{1.0, 1.0, 1.0};
    double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

    vec3 unit_direction = unit_vector(r_in.direction);
    double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
    if (etai_over_etat * sin_theta > 1.0 ) {
        vec3 reflected = reflect(unit_direction, rec.normal);
        scattered = ray{rec.p, reflected};
        return true;
    }
    double reflect_prob = schlick(cos_theta, etai_over_etat);
    if (random_double() < reflect_prob)
    {
        vec3 reflected = reflect(unit_direction, rec.normal);
        scattered = ray{rec.p, reflected};
        return true;
    }
    vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
    scattered = ray{rec.p, refracted};
    return true;
}
