# Ray Tracing in One Weekend

A C++ implementation of the book *
*[Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)** by Peter Shirley.

![alt text](https://github.com/Akamitori/ray_tracing_in_one_weekend/blob/master/final_result.jpg)

## Overview

This project walks through the basics of ray tracing, following the structure from the book. It covers core concepts
like rays, materials, lighting, and advanced features like anti-aliasing and defocus blur.

Key features:

- **Basic Ray Tracing**: Render simple scenes with spheres and basic lighting.
- **Materials**: Add realism with diffuse, reflective, and transparent materials.
- **Anti-Aliasing**: Smooth edges with multi-sampling.
- **Defocus Blur**: Simulate camera effects with depth of field.

## Getting Started

### Prerequisites

- **C++11** or later
- A C++ compiler (`g++`, `clang`, etc.)
- `Make` or `CMake` for building

### Building

1. **Clone the repo**:
   ```shell
   # clone the repo
   git clone https://github.com/Akamitori/ray_tracing_in_one_weekend.git
   
   # change the directory to the repo directory
   cd ray_tracing_in_one_weekend

2. **Build the project**:
   ```shell
   # Using CMake
   mkdir build && cd build
   cmake ..
   make
   ```

3. **Build Configurations**:
    - By default, CMake builds in **Debug mode**, which includes extra debugging symbols and performs less aggressive
      optimizations.

    - To build in **Release mode** for better performance:
      ```shell
      cmake -DCMAKE_BUILD_TYPE=Release ..
      make
      ```

    - To build in **Debug mode** (if needed):
      ```shell
      cmake -DCMAKE_BUILD_TYPE=Debug ..
      make
      ```

### Running

Once built, run the ray tracer:

```bash
./raytracer
```

The output image will be generated as a `.ppm` file with the name `output.ppm`.

## Viewing the output

The output can be viewed with any photo processing program or by using [IrfanView](https://www.irfanview.com/)
or by using this online [PPM viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html)

## Performance notes

Since this is a brute force raytracer it is bound to be slow. The commited code issues the high res settings needed to
produce the image. This generation will take about 5 minutes to 1 hour on release build depending on the number of CPU cores.
This can be sped up by sacrificing some quality in our generation.
Replace this in `main.cpp`

```C++
cam.image_width = 1200;
cam.samples_per_pixel = 500;
cam.max_depth = 50;
```

with

```C++
cam.image_width = 1200;     // we can also reduce image widgh by this is bound to not draw some spheres
cam.samples_per_pixel = 100;
cam.max_depth = 10;
```

## License

This project is licensed under the MIT License.
