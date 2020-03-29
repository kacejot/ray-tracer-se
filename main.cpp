#include <iostream>
#include <fstream>

int main() {
    const int image_width = 320;
    const int image_height = 240;

    std::ofstream file;
    file.open("image.ppm");

    file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i) {
            auto r = static_cast<double>(i) / image_width;
            auto g = static_cast<double>(j) / image_height;
            auto b = 0.2;

            int ir = static_cast<int>(256 * r);
            int ig = static_cast<int>(256 * g);
            int ib = static_cast<int>(256 * b);
            
            file << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::cout << "\nDone.\n";
}
