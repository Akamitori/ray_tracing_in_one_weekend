//
// Created by PETROS on 16/09/2024.
//

#include "material.h"

lambertian::lambertian(const color &albedo) : albedo(albedo) {
}

bool lambertian::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    auto scatter_direction = rec.normal + random_unit_vector();

    // deal with degenerate case where scatter direction is almost zero in all dimensions
    if (scatter_direction.near_zero()) {
        scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
}

metal::metal(const color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {
}

bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation, ray &scattered) const {
    vec3 reflected = reflect(r_in.direction(), rec.normal);
    reflected = unit_vector(reflected) + (fuzz * random_unit_vector());

    scattered = ray(rec.p, reflected);
    attenuation = albedo;
    return dot(scattered.direction(), rec.normal) > 0;
}
