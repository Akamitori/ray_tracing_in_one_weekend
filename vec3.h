#ifndef VEC3_H
#define VEC3_H
#include <assert.h>
#include <ostream>


class vec3 {
public:
    double e[3];

    vec3();

    vec3(double e0, double e1, double e2);

    double x() const;

    double y() const;

    double z() const;

    vec3 operator-() const;

    double operator[](int i) const;

    double &operator[](int i);

    vec3 &operator+=(const vec3 &v);

    vec3 &operator*=(double t);

    vec3 &operator/=(double t);

    [[nodiscard]] double length() const;

    [[nodiscard]] double length_squared() const;

    [[nodiscard]] bool near_zero() const;

    static vec3 random();

    static vec3 random(double min, double max);
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &os, const vec3 &v) {
    return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &lhs, const vec3 &rhs) {
    return vec3{
        lhs.e[0] + rhs.e[0],
        lhs.e[1] + rhs.e[1],
        lhs.e[2] + rhs.e[2]
    };
}

inline vec3 operator-(const vec3 &lhs, const vec3 &rhs) {
    return vec3{
        lhs.e[0] - rhs.e[0],
        lhs.e[1] - rhs.e[1],
        lhs.e[2] - rhs.e[2]
    };
}

inline vec3 operator*(const vec3 &lhs, const vec3 &rhs) {
    return vec3{
        lhs.e[0] * rhs.e[0],
        lhs.e[1] * rhs.e[1],
        lhs.e[2] * rhs.e[2]
    };
}

inline vec3 operator*(const double lhs, const vec3 &rhs) {
    return vec3{
        rhs.e[0] * lhs,
        rhs.e[1] * lhs,
        rhs.e[2] * lhs
    };
}

inline vec3 operator*(const vec3 &lhs, const double rhs) {
    return rhs * lhs;
}

inline vec3 operator/(const vec3 &lhs, const double rhs) {
    return (1 / rhs) * lhs;
}

inline double dot(const vec3 &lhs, const vec3 &rhs) {
    return
            lhs.e[0] * rhs.e[0] +
            lhs.e[1] * rhs.e[1] +
            lhs.e[2] * rhs.e[2];
}

inline vec3 cross(const vec3 &lhs, const vec3 &rhs) {
    return vec3{
        lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1],
        lhs.e[2] * rhs.e[0] - lhs.e[0] * rhs.e[2],
        lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]
    };
}

inline vec3 unit_vector(const vec3 &v) {
    return v / v.length();
}

inline vec3 random_unit_vector() {
    while (true) {
        auto p = vec3::random(-1, 1);
        auto lensq = p.length_squared();
        // avoid extremely small vector errors
        if (1e-160 < lensq && lensq <= 1) {
            return p / sqrt(lensq);
        }
    }
}

inline vec3 random_on_hemisphere(const vec3 &normal) {
    vec3 on_unit_sphere = random_unit_vector();
    if (dot(on_unit_sphere, normal) > 0) {
        return on_unit_sphere;
    } else {
        return -on_unit_sphere;
    }
}

inline vec3 reflect(const vec3& v, const vec3&n) {
    assert(std::fabs(n.length() - 1.0) <= 1e-9);
    return v-2*dot(v,n)*n;
}

#endif
