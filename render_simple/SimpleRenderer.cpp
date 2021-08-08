// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#include "SimpleRenderer.h"
#include "opencv2/opencv.hpp"
#include "Eigen/Eigen"
#include <iostream>

using namespace cv;

cv::Mat pixels_to_cv_mat(uint32_t width, uint32_t height, const std::vector<Eigen::Vector3f> &pixels) {
    uint8_t *data = new uint8_t[width * height * 3];
    for (uint32_t row = 0; row < height; row++) {
        for (uint32_t col = 0; col < width; col++) {
            uint32_t pixel_idx = row * width + col;
            uint32_t data_idx = 3 * ((height - 1 - row) * width + col);
            data[data_idx + 0] = to_color_uint8(pixels.at(pixel_idx).x());
            data[data_idx + 1] = to_color_uint8(pixels.at(pixel_idx).y());
            data[data_idx + 2] = to_color_uint8(pixels.at(pixel_idx).z());
        }
    }
    auto result = Mat(height, width, CV_8UC3, data);
    cvtColor(result, result, COLOR_RGB2BGR);
    return result;
}

void SimpleRenderer::render() {
    Eigen::Matrix4f world_to_screen = viewport_ * projection_ * view_;
    for (uint32_t i = 0; i < mesh_->triangle_count(); i++) {
        SimpleTriangle triangle = vertex_shader(i);
        triangle.v0_ = transform_point(world_to_screen, triangle.v0_);
        triangle.v1_ = transform_point(world_to_screen, triangle.v1_);
        triangle.v2_ = transform_point(world_to_screen, triangle.v2_);
        rasterizer_->rasterize(triangle);
    }
    cv::Mat img_mat = pixels_to_cv_mat(rasterizer_->width(), rasterizer_->height(), rasterizer_->pixels());
    while (waitKey(1) != (int)'q') {
        imshow("Triangle", img_mat);
    }
    img_mat.release();
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