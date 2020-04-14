#pragma once

struct hit_record;
struct ray;

struct hittable {
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};
