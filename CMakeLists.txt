cmake_minimum_required(VERSION 3.29)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 20)

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
)
