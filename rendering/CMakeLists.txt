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
        vshader_impl/SimpleTriVshader.cpp
        vshader_impl/TextureTriVshader.cpp
        texture_impl/SimpleTexture.cpp)
