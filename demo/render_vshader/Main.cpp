// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include <vector>

#include "Eigen/Eigen"
#include "RenderingCore.h"
#include "rasterizer_impl/SimpleRasterizer.h"
#include "shader_impl/SimpleTriShader.h"

int main() {
    uint32_t width = 600;
    uint32_t height = 400;

    SimpleTriShader shader{};
    // Two triangles
    shader.vertices_ = std::vector<Eigen::Vector3f>{
        {-1, -1, 0}, {1, -1, 0}, {1, 1, 0}, {-1, 1, 0}};
    shader.colors_ = std::vector<Eigen::Vector3f>{COLOR_RED, COLOR_BLUE,
                                                   COLOR_GREEN, COLOR_BLUE};
    shader.indices_ = std::vector<Eigen::Vector3i>{{0, 1, 2}, {0, 2, 3}};

    Camera cam{};
    cam.position = Eigen::Vector3f{0, 0, 5};
    cam.forward = Eigen::Vector3f{0, 0, -1};
    cam.up = Eigen::Vector3f{0, 1, 0};

    auto view = cam.to_view();
    auto projection =
        create_perspective(M_PI_4, (float)width / (float)height, 0.1f, 100.f);
    auto viewport = create_viewport(width, height);

    shader.projection_ = &projection;
    shader.view_ = &view;
    shader.viewport_ = &viewport;
    shader.model_ = create_model_matrix({0, 0, 0}, {0, 0, 1}, {0, 1, 0});

    SimpleRasterizer rasterizer{width, height};
    RenderController controller{};
    controller.rasterizer_ = &rasterizer;
    controller.shaders_.push_back(&shader);

    controller.render_iamge();
    controller.show_image("Demo VShader");
    return 0;
}