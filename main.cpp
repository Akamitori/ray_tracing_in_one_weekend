#include <iostream>
#include "color.h"

int main() {
    int image_width = 256;
    int image_height = 256;
    int max_color_value = 255;

    std::cout << "P3\n";
    std::cout << image_width << ' ' << image_height << "\n";
    std::cout << max_color_value << "\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining" << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            
            auto r = static_cast<double>(i) / static_cast<double>(image_width - 1);
            auto g = static_cast<double>(j) / static_cast<double>(image_height - 1);
            auto b = 0.0;

            auto pixel_color=color{r, g, b};
            write_color(std::cout, pixel_color);
        }
    }

    std::clog <<"\rDone.                \n";

    return 0;
}
