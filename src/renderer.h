#pragma once

#include <iostream>
#include <vector>

#include "hittable_list.h"
#include "camera.h"
#include "vec3.h"

class p3_renderer {
public:
    template <typename W, typename C>
    p3_renderer(W&& world, C&& cam, std::ostream& out, size_t image_width, size_t image_height, size_t samples_per_pixel, int max_depth):
        world{std::move(world)},
        cam{std::move(cam)},
        out{out},
        image_width{image_width},
        image_height{image_height},
        samples_per_pixel{samples_per_pixel},
        max_depth{max_depth} {}

    void render();

private:
    std::vector<vec3> render_parallel(size_t start_height, size_t end_heigth);

    hittable_list world;
    camera cam;
    std::ostream& out;
    size_t image_width;
    size_t image_height;
    size_t samples_per_pixel;
    int max_depth;
};
