// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_RASTERIZER_H
#define RENDERING_RASTERIZER_H

#include <cstdint>
#include <vector>
#include "Primitive.h"
#include "Color.h"

class ARasterizer {
public:
    ARasterizer(uint32_t width, uint32_t height) : width_(width), height_(height) {
        pixels_ = std::vector<Eigen::Vector3f>(width * height);
    }

    void set_pixel(uint32_t row, uint32_t col, Eigen::Vector3f color);

    [[nodiscard]] const Eigen::Vector3f &pixel(uint32_t row, uint32_t col) const {
        return pixels_[row * width() + col];
    }

    [[nodiscard]] uint32_t width() const { return width_; }

    [[nodiscard]] uint32_t height() const { return height_; }

    [[nodiscard]] const std::vector<Eigen::Vector3f> &pixels() const { return pixels_; }

    [[nodiscard]] float *data();

    virtual void clear(const Eigen::Vector3f &color);

    virtual void rasterize(IPrimitive &primitive) = 0;

    virtual ~ARasterizer();

protected:
    uint32_t width_;
    uint32_t height_;

private:
    bool synced_{false};
    std::vector<Eigen::Vector3f> pixels_;
    float *pixel_data_{nullptr};
};

#endif //RENDERING_RASTERIZER_H
