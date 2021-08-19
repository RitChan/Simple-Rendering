cmake_minimum_required(VERSION 3.16)
project(ray_tracing)
set(CMAKE_CXX_STANDARD 11)
include_directories(${CMAKE_SOURCE_DIR})
link_libraries(${OpenCV_LIBS})
include_directories(${OpenCV_INCLUDE_DIRS})
add_library(RayTracing
    Structure.cpp
    Shading.cpp
    Data.cpp)