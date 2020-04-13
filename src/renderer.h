#pragma once

#include <iostream>

#include "hittable_list.h"
#include "camera.h"
#include "vec3.h"

class p3_renderer {
public:
    template <typename W, typename C>
    p3_renderer(W&& world, C&& cam, std::ostream& out):
        world{std::move(world)}, cam{std::move(cam)}, out{out} {}

    void render(size_t image_width, size_t image_height, size_t samples_per_pixel, int max_depth);

private:
    hittable_list world;
    camera cam;
    std::ostream& out;
};
