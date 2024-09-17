cmake_minimum_required(VERSION 3.29)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 20)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()

# Add configuration for Debug and Release modes
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_executable(raytracing main.cpp
        rtweekend.h
        vec3.h
        vec3.cpp
        color.cpp
        color.h
        ray.cpp
        ray.h
        RedirectOutput.cpp
        RedirectOutput.h
        hittable.h
        sphere.cpp
        sphere.h
        hittable_list.h
        hittable_list.cpp
        interval.cpp
        interval.h
        camera.cpp
        camera.h
        material.cpp
        material.h
)
