#include <iostream>
#include <fstream>
#include "color.h"
#include "ray.h"
#include "RedirectOutput.h"
#include "sphere.h"

double hit_sphere(const point3 &center, const double radius, const ray &r) {
    const vec3 oc = center - r.origin();

    const auto a = r.direction().length_squared();
    const auto h=  dot(r.direction(),oc);
    const auto c = oc.length_squared() - radius * radius;
    
    const auto discriminant = h*h-a*c;

    if (discriminant < 0) {
        return -1.0;
    }

    return (h - std::sqrt(discriminant)) / a;
}

color ray_color(const ray &r) {
    auto s=sphere{point3{0, 0, -1},0.5};

    hit_record result;
    if(s.hit(r,0,100,result)) {
        vec3 N=result.normal;
        return 0.5 * color{N.x() + 1, N.y() + 1, N.z() + 1};
    }
    // auto t = hit_sphere(point3{0, 0, -1}, 0.5, r);
    // if (t > 0.0) {
    //     
    //     auto sphere_center=vec3{0, 0, -1};
    //     // calcuate the normal which is [Ray at intersection point calculated by t] - [sphere center]
    //     vec3 N = unit_vector(r.at(t) - sphere_center);
    //
    //     // add +1 to all parts of the vector
    //     // this changes the range of each value from [-1,1] to [0,2]
    //     // then multiply by 0.5 to get to the range of [0,1] so we can map to colors
    //     return 0.5 * color{N.x() + 1, N.y() + 1, N.z() + 1};
    // }

    auto unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

int main() {
    // ------------Image-------------------
    auto aspect_ratio = 16. / 9.;
    int image_width = 400;

    // width/height = aspect ratio therefore height= width/aspect;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = image_height < 1 ? 1 : image_height;


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

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone.                \n";

    return 0;
}
