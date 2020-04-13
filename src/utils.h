#pragma once

#include <glm/geometric.hpp>
#include <glm/ext/scalar_constants.hpp>  

#include "hittable.h"
#include "ray.h"

/// Returns a random real in [0,1).
float random();

/// Returns a random real in [min,max).
float random_ranged(float min, float max);

vec3 random_vec();
vec3 random_vec_ranged(float min, float max);
vec3 random_vec_in_unit_sphere();
vec3 random_vec_in_hemisphere(const vec3& normal);
vec3 random_unit_vector();
vec3 linear_gradient(const vec3& from, const vec3& to, const ray& r);
vec3 sphere_gradient(const hit_record& rec, const hittable& world, const int depth);
void gamma_correct(vec3& color, const float gamma);
