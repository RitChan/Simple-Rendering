// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#ifndef RENDER_TRANSFORM_TRANSFORM_RENDERER_H
#define RENDER_TRANSFORM_TRANSFORM_RENDERER_H
#include "RenderingCore.h"
#include "primitive_impl/SimpleTriangle.h"
#include "rasterizer_impl/SimpleRasterizer.h"
#include "Eigen/Eigen"

class TransformRenderer {
public:
    ARasterizer *rasterizer_;
    TriangleMesh *mesh_;
    Camera *camera_;
    Eigen::Matrix4f projection_;
    Eigen::Matrix4f viewport_;

    void vertex_shader(uint32_t index, SimpleTriangle &triangle_out);

    void render();
};

#endif // RENDER_TRANSFORM_TRANSFORM_RENDERER_H