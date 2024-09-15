﻿//
// Created by PETROS on 15/09/2024.
//

#ifndef HITTABLE_H
#define HITTABLE_H

#include <cassert>

#include "ray.h"


class hit_record {
public:
    point3 p;
    vec3 normal;
    double t{};
    bool front_face;

    void set_face_normal(const ray &r, const vec3 &outward_normal) {
        assert(std::fabs(outward_normal.length() - 1.0) <= 1e-9);

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray &r, double ray_t_min, double ray_t_max, hit_record &rec) const = 0;
};


#endif //HITTABLE_H
