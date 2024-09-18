//
// Created by PETROS on 18/09/2024.
//

#ifndef BENCHMARKING_H
#define BENCHMARKING_H
#include <functional>
#include <iostream>
#include <chrono>
#include <functional>  // For std::function
#include <iomanip>     // For formatting output


// Convert microseconds to minutes, seconds, and microseconds
inline void format_duration(long long microseconds) {
    long long total_seconds = microseconds / 1'000'000;
    long long minutes = total_seconds / 60;
    long long seconds = total_seconds % 60;
    long long remaining_microseconds = microseconds % 1'000'000;

    std::cout << std::setfill('0') << minutes << "m "
              << std::setw(2) << seconds << "s "
              << remaining_microseconds << "µs\n";
}

// Generic benchmark function using std::function
inline void benchmark(const std::string& name, const std::function<void()>& func) {
    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    func();  // Execute the function being benchmarked
    auto end = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>(end - start).count();
    std::cout << name << " took: ";
    format_duration(duration);
}


#endif //BENCHMARKING_H
