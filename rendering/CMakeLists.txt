add_library(Rendering STATIC
        core/Color.cpp
        core/Geometry.cpp
        core/Rasterizer.cpp
        core/Event.cpp
        core/Controller.cpp
        core/Factory.cpp
        primitive_impl/SimpleTriangle.cpp
        rasterizer_impl/SimpleRasterizer.cpp
        vshader_impl/SimpleTriVshader.cpp)
