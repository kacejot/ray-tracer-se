#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

struct hittable_list: public hittable {
    std::vector<std::shared_ptr<hittable>> objects;
    
    void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
    void clear() { objects.clear(); }

    bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const override;
};
