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
        pixel_data_ = new float[width * height * 3];
    }

    void set_pixel(uint32_t row, uint32_t col, Eigen::Vector3f color);

    [[nodiscard]] Eigen::Vector3f get_pixel(uint32_t row, uint32_t col) const {
        uint32_t base_idx = 3 * (row * width() + col);
        return {pixel_data_[base_idx + 0],
                pixel_data_[base_idx + 1],
                pixel_data_[base_idx + 2]};
    }

    [[nodiscard]] uint32_t width() const { return width_; }

    [[nodiscard]] uint32_t height() const { return height_; }

    [[nodiscard]] float *data() { return pixel_data_; }

    virtual void clear(const Eigen::Vector3f &color);

    virtual void rasterize(IPrimitive &primitive) = 0;

    virtual ~ARasterizer();

protected:
    uint32_t width_;
    uint32_t height_;

private:
    float *pixel_data_{nullptr};
};

#endif //RENDERING_RASTERIZER_H
