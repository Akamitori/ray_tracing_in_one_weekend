//
// Created by PETROS on 16/09/2024.
//

#include "camera.h"

#include <iostream>

#include "material.h"
#include "RedirectOutput.h"
#include "rtweekend.h"
#include <omp.h>
#include <atomic>

void camera::render(const hittable &world, const bool redirect_output) {
    initialize();


    auto redirect = new RedirectOutput("output.ppm");

    if (!redirect_output) {
        delete redirect;
        redirect = nullptr;
    }

    int max_color_value = 255;
    std::cout << "P3\n";
    std::cout << image_width << ' ' << image_height << "\n";
    std::cout << max_color_value << "\n";

    std::atomic<int> completed_scanlines(0);
    std::vector<color> image_color(image_height * image_width);

#pragma omp parallel for schedule(dynamic, 10), collapse(2)
    for (int j = 0; j < image_height; j++) {
        //std::clog << "\rScanlines remaining" << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            color pixel_color(0, 0, 0);
            for (int sample = 0; sample < samples_per_pixel; sample++) {
                ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            image_color[j * image_width + i] = pixel_samples_scale * pixel_color;
        }

        // Atomically increment the scanline counter
        ++completed_scanlines;

        // Periodically print progress
        if (j % 10 == 0) {  // Print every 10 scanlines
#pragma omp critical
            {
                std::clog << "\rScanlines remaining: " << (image_height - completed_scanlines) << ' ' << std::flush;
            }
        }
    }

    for (auto &pixel: image_color) {
        write_color(std::cout, pixel);
    }

    std::clog << "\rDone.                \n";

    delete redirect;
}


void camera::initialize() {
    // width/height = aspect ratio therefore height= width/aspect;
    // calculate image height based on width and aspect ratio
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;

    // camera center

    // -------------------Determine viewport dimensions-----------------.

    // use the actual aspect ratio because our chosen width and height may not map to the ideal ratio
    // this is an issue because width and height are not rational numbers
    // Also, we both round down image_height and making sure it's at least one.
    // those decisions can make the real ratio differ a lot from the ideal ratio.
    auto theta = degrees_to_radians(vfov);
    auto h = std::tan(theta / 2);
    auto viewport_height = 2.0 * h * focus_dist;
    auto actual_aspect_ratio = (static_cast<double>(image_width) / image_height);
    auto viewport_width = viewport_height * actual_aspect_ratio;

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);


    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = viewport_width * u;
    auto viewport_v = -viewport_height * v;

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left =
            center
            - focus_dist * w
            - viewport_u / 2
            - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors.
    auto defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
}

color camera::ray_color(const ray &r, int depth, const hittable &world) {
    if (depth <= 0) {
        return color{0, 0, 0};
    }

    hit_record rec;
    if (world.hit(r, interval(0.001, infinity), rec)) {
        // get a ray direction that's reflected
        ray scattered;
        color attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, depth - 1, world);
        }
        return color{0, 0, 0};
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

ray camera::get_ray(int i, int j) const {
    // Construct a camera ray originating from the defocus disk and directed at a randomly
    // sampled point around the pixel location i, j.


    auto offset = sample_square();
    auto pixel_sample =
            pixel00_loc +
            ((i + offset.x()) * pixel_delta_u) +
            ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return {ray_origin, ray_direction};
}

vec3 camera::sample_square() {
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
    return {random_double() - 0.5, random_double() - 0.5, 0};
}

point3 camera::defocus_disk_sample() const {
    // Returns a random point in the camera defocus disk.
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
}
