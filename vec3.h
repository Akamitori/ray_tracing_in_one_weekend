#ifndef VEC3_H
#define VEC3_H
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

#endif
