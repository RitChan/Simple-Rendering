// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SIMPLERASTERIZER_H
#define RENDERING_SIMPLERASTERIZER_H
#include "RenderingCore.h"
#include <cstdint>
#include <vector>

class SimpleRasterizer : public ARasterizer {
public:
    SimpleRasterizer(uint32_t width, uint32_t height): ARasterizer(width, height) {
        z_buffer_ = Eigen::MatrixXf(height, width);
        for (uint32_t i = 0; i < height; i++) {
            for (uint32_t j = 0; j < width; j++) {
                z_buffer_(i, j) = -INFINITY;
            }
        }
    }

    void rasterize(IPrimitive &primitive) override;

    void clear(const Eigen::Vector3f &color) override;

private:
    Eigen::MatrixXf z_buffer_;
};

#endif //RENDERING_SIMPLERASTERIZER_H
