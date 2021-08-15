include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(Rendering STATIC
        core/Color.cpp
        core/Geometry.cpp
        core/Rasterizer.cpp
        core/Event.cpp
        core/Controller.cpp
        core/Factory.cpp
        primitive_impl/SimpleTriangle.cpp
        primitive_impl/TextureTriangle.cpp
        rasterizer_impl/SimpleRasterizer.cpp
        shader_impl/SimpleTriShader.cpp
        shader_impl/TextureTriShader.cpp
        texture_impl/SimpleTexture.cpp)
