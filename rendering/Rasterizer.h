// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_RASTERIZER_H
#define RENDERING_RASTERIZER_H

#include <cstdint>
#include <vector>
#include "Primitive.h"
#include "Color.h"

class Rasterizer {
public:
    Rasterizer(uint32_t width, uint32_t height) : width_(width), height_(height) {
        pixels_ = std::vector<Eigen::Vector3f>(width * height);
    }

    [[nodiscard]] Eigen::Vector3f &pixel(uint32_t row, uint32_t col) {
        return pixels_[row * width_ + col];
    }

    [[nodiscard]] const Eigen::Vector3f &pixel(uint32_t row, uint32_t col) const {
        return pixels_[row * width_ + col];
    }

    [[nodiscard]] uint32_t width() const { return width_; }

    [[nodiscard]] uint32_t height() const { return height_; }

    [[nodiscard]] const std::vector<Eigen::Vector3f> &pixels() const { return pixels_; }

    virtual void rasterize(IPrimitive &primitive) = 0;

protected:
    uint32_t width_;
    uint32_t height_;
    std::vector<Eigen::Vector3f> pixels_;
};

#endif //RENDERING_RASTERIZER_H
