#include <algorithm>
#include <future>
#include <thread>

#include "renderer.h"
#include "utils.h"
#include "vec3.h"
#include "ray.h"

std::vector<vec3*> divide_vector_to_chunks(std::vector<vec3>& vector, size_t chunk_size) {
    std::vector<vec3*> result{};

    size_t current_chunk = 0;
    for (; current_chunk < vector.size(); current_chunk += chunk_size) {
        result.push_back(vector.data() + current_chunk);
    }

    return result;
}

void write_fraction_color(std::ostream &out, vec3 vec) {
    vec *= 255.0f;

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(std::clamp(vec.r, 0.0, 255.0)) << ' '
        << static_cast<int>(std::clamp(vec.g, 0.0, 255.0)) << ' '
        << static_cast<int>(std::clamp(vec.b, 0.0, 255.0)) << '\n';
}

void p3_renderer::render(){
    auto threads = static_cast<size_t>(std::thread::hardware_concurrency());
    auto rows_per_thread = image_height / threads + 1;
    
    out << "P3\n" << image_width << " " << image_height << "\n255\n";

    std::vector<std::future<std::vector<vec3>>> futures;
    for (size_t i = 0; i < threads; ++i) {
        auto end_heigth = 
            std::clamp((threads - i) * rows_per_thread, size_t{0}, image_height);
        
        auto start_height = 
            std::clamp(end_heigth - rows_per_thread, size_t{0}, image_height);

        futures.push_back(std::async(std::launch::async, &p3_renderer::render_parallel, this, start_height, end_heigth));
    }

    for (auto&& future : futures) {
        future.wait();
    }

    for (auto&& future : futures) {
        for (auto&& color : future.get()) {
            write_fraction_color(out, color);
        }
    }

    std::cout << "\nDone.\n";
}

std::vector<vec3> p3_renderer::render_parallel(size_t start_height, size_t end_heigth) {
	std::vector<vec3> result;
    for (int j = static_cast<int>(end_heigth) - 1; j >= static_cast<int>(start_height); --j) {
        // some dirty code here
        if (start_height == 0) {
            std::cout << std::endl << "Row's to render: " << j << ' ' << std::flush;
        }

        for (int i = 0; i < static_cast<int>(image_width); ++i) {
            vec3 color{};
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                ray r = cam.cast_ray(u, v);
                color += ray_color(r, world, max_depth);
            }
            color /= static_cast<double>(samples_per_pixel);
            gamma_correct(color, 0.5);
            
			result.push_back(color);
        }
    }

	return result;
}
