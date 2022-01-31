```C++
#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <list>

#include "RenderingCore.h"
#include "framework/GeneralPrimitive.h"
#include "framework/GeneralShader.h"
#include "rasterizer_impl/SimpleRasterizer.h"

struct PrimitiveData {
    // Primitive payload
};

struct ShaderData {
    // Shader payload
};

void shader_reset(IShader *i_shader) {
    // called for every shader at every frame
}

IPrimitive &vertex_shader(IShader *i_shader) {
    // more precisely: primitive shader
}

Eigen::Vector3f fragment_shader(IPrimitive *primitive) {
    // extract color from primitive at cursor
}

int main() {
    // Prepare model data and configure shader

    SimpleRasterizer rasterizer(WIDTH, HEIGHT);
    RenderController controller;
    controller.bg_color = COLOR_BLACK;
    controller.rasterizer_ = &rasterizer;
    // controller.shader_ptrs_.push_back(&shader);
    controller.render_image();
    controller.show_image("Untitled");
    return 0;
}
```
