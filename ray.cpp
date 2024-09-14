//
// Created by PETROS on 14/09/2024.
//


#include "ray.h"

ray::ray() = default;

ray::ray(const point3 &origin, const vec3 &direction): m_origin(origin), m_direction(direction) {
}

const point3 & ray::origin() const {
    return m_origin;
}

const point3 & ray::direction() const {
    return m_direction;
}


point3 ray::at(const double t) const {
    return m_origin + t * m_direction;
}
