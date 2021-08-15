cmake_minimum_required(VERSION 3.16)
project(rendering)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED PATHS "C:/Users/Ritee/MyFiles/r-lib/cxx_lib/opencv_mingw")

include_directories("C:\\Users\\Ritee\\MyFiles\\r-lib\\cxx_lib\\eigen3.3.9")
include_directories(rendering ${OpenCV_INCLUDE_DIRS})
link_libraries(${OpenCV_LIBS})

add_subdirectory(rendering)
add_subdirectory(demo)
add_subdirectory(ray_tracing)