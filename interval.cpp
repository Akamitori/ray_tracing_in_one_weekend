//
// Created by PETROS on 16/09/2024.
//

#include "interval.h"
#include "rtweekend.h"

interval::interval() : min(+infinity), max(-infinity) {
}

interval::interval(const double min, const double max) : min(min), max(max) {
}

double interval::size() const {
    return max - min;
}

bool interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}

double interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
