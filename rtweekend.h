#ifndef RTWEEKEND_H
#define RTWEEKEND_H
#include <limits>
#include <random>


constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double() {
    // Create a random number generator
    static std::random_device rd;  // Seed generator
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    static std::uniform_real_distribution<double> dis(0.0, 1.0); // Uniform distribution in [0, 1)

    return dis(gen); // Generate a random number in the range [0.0, 1.0)
}

inline double random_double(double min, double max) {
    // Create a random number generator
    static std::random_device rd;  // Seed generator
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<double> dis(0.0, 1.0); // Uniform distribution in [0, 1)
    
    return dis(gen);
}

#endif