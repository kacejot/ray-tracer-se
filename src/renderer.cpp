#include <algorithm>

#include "renderer.h"
#include "utils.h"
#include "vec3.h"
#include "ray.h"

void write_fraction_color(std::ostream &out, vec3 vec);

void p3_renderer::render(size_t image_width, size_t image_height, size_t samples_per_pixel, int max_depth){
        out << "P3\n" << image_width << " " << image_height << "\n255\n";
        for (int j = static_cast<int>(image_height) - 1; j >= 0; --j) {
            std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < static_cast<int>(image_width); ++i) {
                vec3 color{};
                for (int s = 0; s < samples_per_pixel; ++s) {
                    auto u = (i + random()) / image_width;
                    auto v = (j + random()) / image_height;
                    ray r = cam.cast_ray(u, v);
                    color += ray_color(r, world, max_depth);
                }
                color /= float(samples_per_pixel);
                gamma_correct(color, 0.5f);
                write_fraction_color(out, color);
            }
        }

        std::cout << "\nDone.\n";
}

void write_fraction_color(std::ostream &out, vec3 vec) {
    vec *= 255.0f;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(std::clamp(vec.r, 0.0f, 255.f)) << ' '
        << static_cast<int>(std::clamp(vec.g, 0.0f, 255.f)) << ' '
        << static_cast<int>(std::clamp(vec.b, 0.0f, 255.f)) << '\n';
}
