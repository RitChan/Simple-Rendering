// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include "RenderingCore.h"
#include "TransformRenderer.h"

using namespace std;
using namespace Eigen;

int main() {
    TriangleMesh mesh{};
    SimpleRasterizer rasterizer{600, 400};
    TransformRenderer renderer{};
    renderer.mesh_ = &mesh;
    renderer.rasterizer_ = &rasterizer;

    // A box
    mesh.vertices = vector<Vector3f>{
        // 前面
        {-1, -1, 1},  // 0 左下前
        {1, -1, 1},   // 1 右下前
        {1, 1, 1},    // 2 右上前
        {-1, 1, 1},   // 3 左上前
        // 左面
        {-1, -1, 1},   // 4 左下前
        {-1, 1, 1},    // 5 左上前
        {-1, 1, -1},   // 6 左上后
        {-1, -1, -1},  // 7 左下后
        // 后面
        {-1, -1, -1},  // 8 左下后
        {-1, 1, -1},   // 9 左上后
        {1, 1, -1},    // 10 右上后
        {1, -1, -1},   // 11 右下后
        // 右面
        {1, -1, -1},  // 12 右下后
        {1, 1, -1},   // 13 右上后
        {1, 1, 1},    // 14 右上前
        {1, -1, 1},   // 15 右下前
        // 上面
        {-1, 1, 1},   // 16 左上前
        {1, 1, 1},    // 17 右上前
        {1, 1, -1},   // 18 右上后
        {-1, 1, -1},  // 19 左上后
        // 下面
        {-1, -1, 1},   // 20 左下前
        {-1, -1, -1},  // 21 左下后
        {1, -1, -1},   // 22 右下后
        {1, -1, 1}     // 23 右下前
    };

    mesh.colors =
        vector<Vector3f>{// 前面
                         COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                         // 左面
                         COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
                         // 后面
                         COLOR_RED, COLOR_RED, COLOR_RED, COLOR_RED,
                         // 右面
                         COLOR_BLUE, COLOR_BLUE, COLOR_BLUE, COLOR_BLUE,
                         // 上面
                         COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN,
                         // 下面
                         COLOR_GREEN, COLOR_GREEN, COLOR_GREEN, COLOR_GREEN};

    mesh.indices = vector<Vector3i>{//上面
                                    {0, 1, 2},
                                    {0, 2, 3},
                                    // 左面
                                    {4, 5, 6},
                                    {4, 6, 7},
                                    // 后面
                                    {8, 9, 10},
                                    {8, 10, 11},
                                    // 右面
                                    {12, 13, 14},
                                    {12, 14, 15},
                                    // 上面
                                    {16, 17, 18},
                                    {16, 18, 19},
                                    // 下面
                                    {20, 21, 22},
                                    {20, 22, 23}};

    mesh.world_mat = create_model_matrix({0, 0, 0}, {1, 1, 1}, {0, 1, -1});
    Camera camera{};
    camera.position = Eigen::Vector3f{0, 0, 8};
    camera.forward = Eigen::Vector3f{0, 0, -1};
    camera.up = Eigen::Vector3f{0, 1, 0};
    renderer.camera_ = &camera;
    renderer.projection_ = create_perspective(M_PI_4, 1.5f, 0.1, 100);
    renderer.viewport_ = create_viewport(600, 400);

    renderer.render();
    return 0;
}