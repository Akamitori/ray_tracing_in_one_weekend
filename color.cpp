//
// Created by PETROS on 14/09/2024.
//

#include "color.h"
#include "interval.h"

void write_color(std::ostream &os, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255]
    static const interval intensity(0.000,0.999);
    int rbyte = static_cast<int>(256 * intensity.clamp(r));
    int gbyte = static_cast<int>(256 * intensity.clamp(g));
    int bbyte = static_cast<int>(256 * intensity.clamp(b));

    os << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
