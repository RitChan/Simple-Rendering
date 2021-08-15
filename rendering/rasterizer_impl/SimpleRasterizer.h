// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SIMPLERASTERIZER_H
#define RENDERING_SIMPLERASTERIZER_H
#include <cstdint>
#include <vector>

#include "RenderingCore.h"

class SimpleRasterizer : public ARasterizer {
   public:
    SimpleRasterizer(uint32_t width, uint32_t height)
        : ARasterizer(width, height) {
        z_buffer_ = Eigen::MatrixXf(height, width);
        z_buffer_.setConstant(-INFINITY);
    }

    void rasterize(IPrimitive &primitive) override;

    void clear(const Eigen::Vector3f &color) override;

   private:
    Eigen::MatrixXf z_buffer_;
};

#endif  // RENDERING_SIMPLERASTERIZER_H
