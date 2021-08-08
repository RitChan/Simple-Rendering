// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "SimpleRasterizer.h"
#include "Eigen/Eigen"

void SimpleRasterizer::rasterize(IPrimitive &primitive) {
    auto bbox = primitive.get_bbox();
    for (uint32_t row = std::max(0, bbox.bottom_); row < std::min((int)bbox.top_, (int)height_); row++) {
        for (uint32_t col = std::max(0, bbox.left_); col < std::min((int)bbox.right_, (int)width_); col++) {
            float cy = row + 0.5f;
            float cx = col + 0.5f;
            primitive.set_cursor(cx, cy);
            if (primitive.is_inside()) {
                float interpolated_z = primitive.interpolated_z();
                // right handed
                if (interpolated_z > z_buffer_(row, col)) {
                    z_buffer_(row, col) = interpolated_z;
                    auto *shader = primitive.get_shader();
                    pixel(row, col) = shader->get_color();
                    delete shader;
                }
            }
        }
    }
}