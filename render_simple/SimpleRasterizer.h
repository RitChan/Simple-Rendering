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
        z_buffer_ = Eigen::MatrixXf(width, height);
    }

    void rasterize(IPrimitive &primitive) override;

private:
    Eigen::MatrixXf z_buffer_;
};

#endif //RENDERING_SIMPLERASTERIZER_H
