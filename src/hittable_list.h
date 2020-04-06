#pragma once

#include <memory>
#include <vector>
#include "hittable.h"

struct hittable_list: public hittable {
    std::vector<std::shared_ptr<hittable>> objects;
    
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
    void clear() { objects.clear(); }

    bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const override;
};

bool hittable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}