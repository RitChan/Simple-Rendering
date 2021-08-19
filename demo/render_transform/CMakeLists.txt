link_libraries(Rendering)
include_directories(${PROJECT_SOURCE_DIR}/rendering)
add_executable(demo_transform
    Main.cpp
    TransformRenderer.cpp)
