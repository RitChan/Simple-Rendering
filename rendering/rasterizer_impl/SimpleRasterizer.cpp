// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "SimpleRasterizer.h"

#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <cstdlib>

void SimpleRasterizer::rasterize(IPrimitive &primitive) {
    auto bbox = primitive.get_bbox();
    for (uint32_t row = std::max(0, bbox.bottom_);
         row < (uint32_t)std::min((int)bbox.top_, (int)height_); row++) {
        for (uint32_t col = std::max(0, bbox.left_);
             col < (uint32_t)std::min((int)bbox.right_, (int)width_); col++) {
            float cy = row + 0.5f;
            float cx = col + 0.5f;
            primitive.set_cursor(cx, cy);
            if (primitive.is_inside()) {
                float interpolated_z = primitive.interpolated_z();
                // right handed
                if (std::abs(interpolated_z) < 1 &&
                    interpolated_z > z_buffer_(row, col)) {
                    z_buffer_(row, col) = interpolated_z;
                    set_pixel(row, col, primitive.get_color());
                }
            }
        }
    }
}

void SimpleRasterizer::clear(const Eigen::Vector3f &color) {
    ARasterizer::clear(color);
    z_buffer_.setConstant(-INFINITY);
}