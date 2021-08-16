include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package(SDL2 REQUIRED)
link_libraries(mingw32 SDL2::SDL2main SDL2::SDL2 SDL2_image gsl)
add_executable(rt_main 
    RT_main.c
    RT_assert.c
    RT_linalg.c)