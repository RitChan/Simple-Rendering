// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <fstream>
#include <list>
#include <vector>

#include "RenderingCore.h"
#include "rasterizer_impl/SimpleRasterizer.h"
#include "shader_impl/MeshDepthShader.h"


int main() {
    const uint32_t WIDTH = 600;
    const uint32_t HEIGHT = 400;
    std::list<TriangleMesh *> meshes;
    bool loaded = load_obj_meshes("..\\..\\..\\resource\\ring.obj", meshes);
    if (!loaded) {
        std::cout << "Failed to load mesh" << std::endl;
        return -1;
    }
    auto shader = MeshDepthShader();
    shader.barycentric_tolerance_ = 0.1;
    shader.bfc_ = true;
    shader.ccw_ = true;
    shader.color_ = COLOR_WHITE;
    shader.near_bright_ = true;
    shader.exp_ = 1;
    shader.depth_norm_scalar_ = 1;
    shader.mesh_ = meshes.front();
    shader.model_mat_ = create_scale_matrix(50);
    shader.model_mat_ = create_rotation_x(-EIGEN_PI / 4) * shader.model_mat_;
    shader.model_mat_ = create_rotation_y(EIGEN_PI / 6) * shader.model_mat_;
    auto view = create_view_matrix({0, 0, 30}, {0, 0, -1}, {0, 1, 0});
    auto project = create_perspective(EIGEN_PI / 4, (float)WIDTH / HEIGHT, 0.1f, 100.f);
    auto viewport = create_viewport(WIDTH, HEIGHT);
    shader.view_ = &view;
    shader.project_ = &project;
    shader.viewport_ = &viewport;
    SimpleRasterizer rasterizer(WIDTH, HEIGHT);
    RenderController controller;
    controller.bg_color = COLOR_WHITE;
    controller.rasterizer_ = &rasterizer;
    controller.shader_ptrs_.push_back(&shader);
    controller.show_fps_ = true;
    controller.show_image_ = true;
    controller.loop_forever("Obj Loader (Depth)");
    // controller.render_iamge();
    // controller.render_iamge();
    // controller.show_image("Depth");
    return 0;
}