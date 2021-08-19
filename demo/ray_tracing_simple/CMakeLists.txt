include_directories(${CMAKE_SOURCE_DIR}/ray_tracing)
link_libraries(RayTracing)
add_executable(ray_tracing_simple Main.cpp)
