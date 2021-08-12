// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include <vector>

#include "Eigen/Eigen"
#include "RenderingCore.h"
#include "rasterizer_impl/SimpleRasterizer.h"
#include "vshader_impl/SimpleTriVshader.h"

int main() {
    uint32_t width = 600;
    uint32_t height = 400;

    SimpleTriVshader vshader{};
    // Two triangles
    vshader.vertices_ = std::vector<Eigen::Vector3f>{
        {-1, -1, 0}, {1, -1, 0}, {1, 1, 0}, {-1, 1, 0}};
    vshader.colors_ = std::vector<Eigen::Vector3f>{COLOR_RED, COLOR_BLUE,
                                                   COLOR_GREEN, COLOR_BLUE};
    vshader.indices_ = std::vector<Eigen::Vector3i>{{0, 1, 2}, {0, 2, 3}};

    Camera cam{};
    cam.position = Eigen::Vector3f{0, 0, 5};
    cam.forward = Eigen::Vector3f{0, 0, -1};
    cam.up = Eigen::Vector3f{0, 1, 0};

    auto view = cam.to_view();
    auto projection =
        create_perspective(M_PI_4, (float)width / (float)height, 0.1f, 100.f);
    auto viewport = create_viewport(width, height);

    vshader.projection_ = &projection;
    vshader.view_ = &view;
    vshader.viewport_ = &viewport;
    vshader.model_ = create_model_matrix({0, 0, 0}, {0, 0, 1}, {0, 1, 0});

    SimpleRasterizer rasterizer{width, height};
    RenderController controller{};
    controller.rasterizer_ = &rasterizer;
    controller.vshaders_.push_back(&vshader);

    controller.render_iamge();
    controller.show_image("Demo VShader");
    return 0;
}