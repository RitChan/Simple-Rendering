add_library(Rendering STATIC
        core/Color.cpp
        core/Geometry.cpp
        core/Rasterizer.cpp
        primitive_impl/SimpleTriangle.cpp
        rasterizer_impl/SimpleRasterizer.cpp)
