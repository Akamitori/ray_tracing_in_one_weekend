#include <iostream>

int main() {
    int image_width = 256;
    int image_height = 256;
    int max_color_value = 255;

    std::cout << "P3\n";
    std::cout << image_width << ' ' << image_height << "\n";
    std::cout << max_color_value << "\n";

    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            std::clog << "\rScanlines remaining" << (image_height - j) << ' ' << std::flush;
            auto r = static_cast<double>(i) / static_cast<double>(image_width - 1);
            auto g = static_cast<double>(j) / static_cast<double>(image_height - 1);
            auto b = 0.0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog <<"\rDone.                \n";

    return 0;
}
