// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#include "SimpleRenderer.h"

#include <iostream>

#include "Eigen/Eigen"
#include "opencv2/opencv.hpp"

void SimpleRenderer::render() {
    Eigen::Matrix4f world_to_screen = viewport_ * projection_ * view_;
    for (uint32_t i = 0; i < mesh_->triangle_count(); i++) {
        SimpleTriangle triangle = vertex_shader(i);
        triangle.v0_ = transform_point(world_to_screen, triangle.v0_);
        triangle.v1_ = transform_point(world_to_screen, triangle.v1_);
        triangle.v2_ = transform_point(world_to_screen, triangle.v2_);
        rasterizer_->rasterize(triangle);
    }
    cv::Mat img_mat = cv::Mat(rasterizer_->height(), rasterizer_->width(),
                              CV_32FC3, rasterizer_->data());
    cv::flip(img_mat, img_mat, 0);
    imshow("Triangle", img_mat);
    cv::waitKey();
}

SimpleTriangle SimpleRenderer::vertex_shader(uint32_t tri_index) {
    SimpleTriangle result;
    Eigen::Vector3i &v_idx = mesh_->indices.at(tri_index);
    result.color0_ = mesh_->colors[v_idx.x()];
    result.color1_ = mesh_->colors[v_idx.y()];
    result.color2_ = mesh_->colors[v_idx.z()];
    result.v0_ = transform_point(mesh_->world_mat, mesh_->vertices[v_idx.x()]);
    result.v1_ = transform_point(mesh_->world_mat, mesh_->vertices[v_idx.y()]);
    result.v2_ = transform_point(mesh_->world_mat, mesh_->vertices[v_idx.z()]);
    return result;
}