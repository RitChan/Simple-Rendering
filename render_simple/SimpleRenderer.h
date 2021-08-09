// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SIMPLERENDERER_H
#define RENDERING_SIMPLERENDERER_H

#include "RenderingCore.h"
#include "Eigen/Eigen"
#include "primitive_impl/SimpleTriangle.h"
#include "opencv2/opencv.hpp"

cv::Mat pixels_to_cv_mat(uint32_t width, uint32_t height, const std::vector<Eigen::Vector3f> &pixels);

class SimpleRenderer {
public:
    void render();
    SimpleTriangle vertex_shader(uint32_t tri_index);

    ARasterizer *rasterizer_{nullptr};
    TriangleMesh *mesh_{nullptr};
    Eigen::Matrix4f view_;
    Eigen::Matrix4f projection_;
    Eigen::Matrix4f viewport_;
};

#endif //RENDERING_SIMPLERENDERER_H
