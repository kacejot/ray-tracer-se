#pragma once

#include "hittable.h"
#include "ray.h"

constexpr double pi = 3.1415926535897932385;

/// Returns a random real in [0,1).
double random_double();

/// Returns a random real in [min,max).
double random_double_ranged(double min, double max);

vec3 random_vec();
vec3 random_vec_ranged(double min, double max);
vec3 random_vec_in_unit_sphere();
vec3 random_vec_in_hemisphere(const vec3& normal);
vec3 random_unit_vector();
vec3 linear_gradient(const vec3& from, const vec3& to, const ray& r);
vec3 sphere_gradient(const hit_record& rec, const hittable& world, const int depth);
void gamma_correct(vec3& color, const double gamma);
