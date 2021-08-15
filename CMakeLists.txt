cmake_minimum_required(VERSION 3.16)
project(rendering)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

add_compile_options("-Og")

find_package(OpenCV REQUIRED PATHS)

include_directories(rendering ${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_subdirectory(rendering)
add_subdirectory(demo)
add_subdirectory(ray_tracing)