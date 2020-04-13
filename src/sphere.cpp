#include <glm/geometric.hpp>

#include "hit_record.h"
#include "sphere.h"
#include "ray.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    auto oc = r.origin - center;
    auto a = glm::dot(r.direction, r.direction);
    auto half_b = glm::dot(oc, r.direction);
    auto c = glm::dot(oc, oc) - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant > 0) {
        auto root = sqrt(discriminant);
        
        auto temp = (-half_b - root)/a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
			rec.p = r.at(rec.t);
			rec.set_face_normal(r, glm::normalize(rec.p - center));
            rec.mat_ptr = mat_ptr;
			return true;
        }
        
        temp = (-half_b + root) / a;
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
			rec.p = r.at(rec.t);
			rec.set_face_normal(r, glm::normalize(rec.p - center));
            rec.mat_ptr = mat_ptr;
			return true;
        }
    }
    return false;
}
