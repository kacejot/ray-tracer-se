#pragma once

struct hit_record;
struct ray;

struct hittable {
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};
