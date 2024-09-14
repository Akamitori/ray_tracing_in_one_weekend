cmake_minimum_required(VERSION 3.29)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracing main.cpp
        vec3.cpp
        vec3.h
        color.cpp
        color.h
        ray.cpp
        ray.h
        RedirectOutput.cpp
        RedirectOutput.h)
