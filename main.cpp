
#include <iostream>

#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "RedirectOutput.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // ------------Image-------------------
    auto aspect_ratio = 16. / 9.;
    int image_width = 400;

    // width/height = aspect ratio therefore height= width/aspect;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;

    // World

    // World

    hittable_list world;
    world.add(std::make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(std::make_shared<sphere>(point3(0,-100.5,-1), 100));


    //----------------Camera------------------------
    auto focal_length = 1.0f;
    auto viewport_height = 2.0f;

    // use the actual aspect ratio because our chosen width and height may not map to the ideal ratio
    // this is an issue because width and height are not rational numbers
    // Also, we both round down image_height and making sure it's at least one.
    // those decisions can make the real ratio differ a lot from the ideal ratio.
    auto actual_aspect_ratio = static_cast<double>(image_width) / image_height;
    auto viewport_width = viewport_height * actual_aspect_ratio;
    auto camera_center = point3{0, 0, 0};

    // Calculate the vectors across the horizontal and down the vertical viewport edges (always in terms of the camera)
    auto viewport_u = vec3{viewport_width, 0, 0};
    auto viewport_v = vec3{0, -viewport_height, 0};

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel
    auto viewport_upper_left =
            camera_center
            - vec3(0, 0, focal_length) // z negative is pointing towards viewport and camera is at focal length distance
            - viewport_u / 2
            - viewport_v / 2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //-----------------------Render------------------
    RedirectOutput redirect("output.ppm");

    int max_color_value = 255;
    std::cout << "P3\n";
    std::cout << image_width << ' ' << image_height << "\n";
    std::cout << max_color_value << "\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining" << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + i * pixel_delta_u + j * pixel_delta_v;
            auto ray_direction = pixel_center - camera_center;
            ray r{camera_center, ray_direction};

            color pixel_color = ray_color(r,world);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                \n";

    return 0;
}
