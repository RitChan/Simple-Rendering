// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SIMPLERASTERIZER_H
#define RENDERING_SIMPLERASTERIZER_H
#include "Rendering.h"
#include <cstdint>
#include <vector>

class SimpleRasterizer : public Rasterizer {
public:
    SimpleRasterizer(uint32_t width, uint32_t height): Rasterizer(width, height) {
        z_buffer_ = Eigen::MatrixXf(height, width);
        for (uint32_t i = 0; i < height; i++) {
            for (uint32_t j = 0; j < width; j++) {
                z_buffer_(i, j) = -INFINITY;
            }
        }
    }

    void rasterize(IPrimitive &primitive) override;

private:
    Eigen::MatrixXf z_buffer_;
};

#endif //RENDERING_SIMPLERASTERIZER_H
