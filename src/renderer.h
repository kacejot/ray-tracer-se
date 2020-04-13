#pragma once

#include <iostream>

#include <glm/vec3.hpp>

#include "hittable_list.h"
#include "camera.h"

class p3_renderer {
public:
    template <typename W, typename C>
    p3_renderer(W&& world, C&& cam, std::ostream& out):
        world{std::move(world)}, cam{std::move(cam)}, out{out} {}

    void render(size_t image_width, size_t image_height, size_t samples_per_pixel, size_t max_depth);

private:
    hittable_list world;
    camera cam;
    std::ostream& out;
};

void write_vec3(std::ostream &out, const glm::vec3& vec);
