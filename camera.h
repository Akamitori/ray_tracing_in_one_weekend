//
// Created by PETROS on 16/09/2024.
//

#ifndef CAMERA_H
#define CAMERA_H


#include "color.h"
#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0;  // Ratio of image width over height
    int    image_width  = 100;  // Rendered image width in pixel count
    
    void render(const hittable&world, bool redirect_output = false);
private:
    int    image_height;   // Rendered image height
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below
    
    void initialize();
    [[nodiscard]] static color ray_color(const ray& r, const hittable& world);
};



#endif //CAMERA_H
