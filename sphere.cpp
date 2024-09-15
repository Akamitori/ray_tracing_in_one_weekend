//
// Created by PETROS on 15/09/2024.
//

#include "sphere.h"

sphere::sphere(const point3 &center, const double radius) : center(center), radius(std::fmax(0, radius)) {
}

bool sphere::hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec) const {
    const vec3 oc = center - r.origin();

    const auto a = r.direction().length_squared();
    const auto h = dot(r.direction(), oc);
    const auto c = oc.length_squared() - radius * radius;

    const auto discriminant = h * h - a * c;

    if (discriminant < 0) {
        return false;
    }

    auto sqrt_discriminant = sqrt(discriminant);

    auto root = (h - sqrt_discriminant) / a;

    if (root <= ray_t_min && ray_t_max <= root) {
        root = (h + sqrt_discriminant) / a;
        if (root <= ray_t_min && ray_t_max <= root) {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;

    return true;
};
