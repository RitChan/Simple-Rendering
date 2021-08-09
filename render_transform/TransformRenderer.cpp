// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#include "TransformRenderer.h"

#include "Eigen/Eigen"
#include "opencv2/opencv.hpp"

void TransformRenderer::vertex_shader(uint32_t index,
                                      SimpleTriangle &triangle_out) {
    Eigen::Vector3i tri_idx = mesh_->indices[index];
    triangle_out.v0_ =
        transform_point(mesh_->world_mat, mesh_->vertices.at(tri_idx.x()));
    triangle_out.v1_ =
        transform_point(mesh_->world_mat, mesh_->vertices.at(tri_idx.y()));
    triangle_out.v2_ =
        transform_point(mesh_->world_mat, mesh_->vertices.at(tri_idx.z()));
    triangle_out.color0_ = mesh_->colors.at(tri_idx.x());
    triangle_out.color1_ = mesh_->colors.at(tri_idx.y());
    triangle_out.color2_ = mesh_->colors.at(tri_idx.z());
    triangle_out.set_cursor(triangle_out.v0_.x(), triangle_out.v0_.y());
}

void TransformRenderer::render() {
    SimpleTriangle triangle;
    int32_t key = 0;
    cv::Mat img_mat = cv::Mat(rasterizer_->height(), rasterizer_->width(),
                              CV_32FC3, rasterizer_->data());
    cv::flip(img_mat, img_mat, 0);
    while (key != 'q') {
        rasterizer_->clear({0, 0, 0});
        Eigen::Matrix4f world_2_screen =
            viewport_ * projection_ * camera_->to_view();
        for (uint32_t i = 0; i < mesh_->triangle_count(); i++) {
            vertex_shader(i, triangle);
            triangle.v0_ = transform_point(world_2_screen, triangle.v0_);
            triangle.v1_ = transform_point(world_2_screen, triangle.v1_);
            triangle.v2_ = transform_point(world_2_screen, triangle.v2_);
            rasterizer_->rasterize(triangle);
        }
        cv::imshow("Render Transform", img_mat);
        key = cv::waitKey(1);
        printf("Tick....\n");
        switch (key) {
            case 'd':
                camera_->move({0.5f, 0, 0});
                break;
            case 'a':
                camera_->move({-0.5f, 0, 0});
                break;
            case 'w':
                camera_->move({0, 0, -0.5f});
                break;
            case 's':
                camera_->move({0, 0, 0.5f});
                break;
            default:
                break;
        }
    }
}
