cmake_minimum_required(VERSION 3.16)
project(rendering)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

add_compile_options("-O2" "-Wall")

find_package(OpenCV REQUIRED)

add_subdirectory(rendering)
add_subdirectory(demo)
add_subdirectory(ray_tracing)
