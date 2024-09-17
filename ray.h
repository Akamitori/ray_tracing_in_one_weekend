//
// Created by PETROS on 14/09/2024.
//

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

// Ray is pretty much a function P(t)=A+tb;
// A is the origin, b is the ray direction and t is a real number used to move along the ray

class ray {
public:
    ray();

    ray(const point3 &origin, const vec3 &direction);

    [[nodiscard]] const point3 &origin() const;

    [[nodiscard]] const point3 &direction() const;

    [[nodiscard]] point3 at(double t) const;

private:
    point3 m_origin;
    vec3 m_direction;

};


#endif //RAY_H
