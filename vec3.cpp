// //
// // Created by PETROS on 14/09/2024.
// //
//
#include "vec3.h"
#include <cmath>

#include "rtweekend.h"

vec3::vec3() : e{0, 0, 0} {
}

vec3::vec3(const double e0, const double e1, const double e2) : e{e0, e1, e2} {
}

double vec3::x() const {
    return e[0];
}

double vec3::y() const {
    return e[1];
}

double vec3::z() const {
    return e[2];
}

vec3 vec3::operator-() const {
    return vec3{-e[0], -e[1], -e[2]};
}

double vec3::operator[](const int i) const {
    return e[i];
}

double &vec3::operator[](const int i) {
    return e[i];
}

vec3 &vec3::operator+=(const vec3 &rhs) {
    e[0] += rhs.e[0];
    e[1] += rhs.e[1];
    e[2] += rhs.e[2];
    return *this;
}

vec3 &vec3::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

vec3 &vec3::operator/=(const double t) {
    return *this *= 1 / t;
}

double vec3::length() const {
    return std::sqrt(length_squared());
}

double vec3::length_squared() const {
    return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

bool vec3::near_zero() const {
    // Return true if the vector is close to zero in all dimensions.
    auto s = 1e-8;
    return
            std::fabs(e[0]) < s &&
            std::fabs(e[1]) < s &&
            std::fabs(e[2]) < s;
}

vec3 vec3::random() {
    return {
            random_double(),
            random_double(),
            random_double()
    };
}

vec3 vec3::random(double min, double max) {
    return {
            random_double(min, max),
            random_double(min, max),
            random_double(min, max)
    };
}
