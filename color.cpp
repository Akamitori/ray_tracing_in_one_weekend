//
// Created by PETROS on 14/09/2024.
//

#include "color.h"

void write_color(std::ostream &os, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255]
    int rbyte = static_cast<int>(255.999 * r);
    int gbyte = static_cast<int>(255.999 * g);
    int bbyte = static_cast<int>(255.999 * b);

    os << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
