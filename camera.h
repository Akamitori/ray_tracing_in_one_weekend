//
// Created by PETROS on 16/09/2024.
//

#ifndef CAMERA_H
#define CAMERA_H


#include "color.h"
#include "hittable.h"

class camera {
public:
    double aspect_ratio = 1.0; // Ratio of image width over height
    int image_width = 100; // Rendered image width in pixel count
    int samples_per_pixel = 10;  // Count of random samples for each pixel
    int max_depth = 10;  // Maximum number of ray bounces into scene


    double vfov = 90; // Vertical view angle (field of view)
    point3 lookfrom{0, 0, 0}; // Point camera is looking from
    point3 lookat{0, 0, -1}; // Point camera is looking at
    point3 vup{0, 1, 0}; // Camera-relative "up" direction

    double defocus_angle = 0;  // Variation angle of rays through each pixel
    double focus_dist = 10;    // Distance from camera lookfrom point to plane of perfect focus

    void render(const hittable &world, bool redirect_output = false);

private:
    int image_height = 0; // Rendered image height
    double pixel_samples_scale = 0;
    point3 center; // Camera center
    point3 pixel00_loc; // Location of pixel 0, 0
    vec3 pixel_delta_u; // Offset to pixel to the right
    vec3 pixel_delta_v; // Offset to pixel below
    vec3 u, v, w; // camera frame basis vectors;

    vec3   defocus_disk_u;       // Defocus disk horizontal radius
    vec3   defocus_disk_v;       // Defocus disk vertical radius


    void initialize();

    [[nodiscard]] static color ray_color(const ray &r, int depth, const hittable &world);

    [[nodiscard]] ray get_ray(int i, int j) const;

    [[nodiscard]] static vec3 sample_square();

    [[nodiscard]]point3 defocus_disk_sample() const;
};


#endif //CAMERA_H
