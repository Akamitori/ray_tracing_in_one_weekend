cmake_minimum_required(VERSION 3.29)
project(ray_tracing_in_one_weekend)

set(CMAKE_CXX_STANDARD 20)

# Set default build type to Release if not specified
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()

# Define the name of the executable
set(EXECUTABLE_NAME raytracing)

add_executable(${EXECUTABLE_NAME} main.cpp
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

# Extreme optimization flags for MSVC
if (MSVC)
    target_compile_options(${EXECUTABLE_NAME} PRIVATE
            # Debug mode
            $<$<CONFIG:DEBUG>:/Zi>

            # Release mode: Aggressive optimizations
            $<$<CONFIG:RELEASE>:/O2 /Ob2 /Ot /Oi /GL /fp:fast /arch:AVX2 /GF /Gy /Zc:inline /favor:INTEL64 /GS->
    )

    # Linker options for MSVC
    target_link_options(${EXECUTABLE_NAME} PRIVATE
            $<$<CONFIG:RELEASE>:/LTCG /INCREMENTAL:NO /OPT:REF /OPT:ICF>
    )
else()
    # Extreme optimization flags for GCC/Clang
    target_compile_options(${EXECUTABLE_NAME} PRIVATE
            # Debug mode
            $<$<CONFIG:DEBUG>:-g>

            # Release mode: Aggressive optimizations
            $<$<CONFIG:RELEASE>:-O3 -march=native -mtune=native -ffast-math -funroll-loops -flto -fomit-frame-pointer
            -fassociative-math -freciprocal-math -fno-trapping-math -frename-registers>
    )

    # Linker options for GCC/Clang
    target_link_options(${EXECUTABLE_NAME} PRIVATE
            $<$<CONFIG:RELEASE>:-flto>
    )
endif()


# Link OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()
