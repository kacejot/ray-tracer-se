#include <fstream>

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "hittable_list.h"
#include "constants.h"
#include "renderer.h"
#include "sphere.h"
#include "camera.h"

int main() {
    std::ofstream file;
    file.open("image.ppm");

    hittable_list world;

    world.add(std::make_shared<sphere>(
        glm::vec3{0, 0, -1}, 0.5,
        std::make_shared<lambertian>(glm::vec3{0.7, 0.3, 0.3})));

    world.add(std::make_shared<sphere>(
        glm::vec3{0, -100.5, -1}, 100,
        std::make_shared<lambertian>(glm::vec3{0.8, 0.8, 0.0})));

    world.add(std::make_shared<sphere>(
        glm::vec3{1, 0, -1}, 0.5,
        std::make_shared<metal>(glm::vec3{0.8, 0.6, 0.2})));
    
    world.add(std::make_shared<sphere>(
        glm::vec3{-1, 0, -1}, 0.5,
        std::make_shared<metal>(glm::vec3{0.8, 0.8, 0.8})));

   p3_renderer{
        std::move(world),
        camera{},
        file
    }.render(IMAGE_WIDTH, IMAGE_HEIGHT, SAMPLES_PER_PIXEL, MAX_DEPTH);
}