// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "core/Rasterizer.h"

// Non-virtual
void ARasterizer::set_pixel(uint32_t row, uint32_t col, Eigen::Vector3f color) {
    uint32_t pixel_data_idx = (row * width() + col) * 3;
    data()[pixel_data_idx + 0] = color.x();
    data()[pixel_data_idx + 1] = color.y();
    data()[pixel_data_idx + 2] = color.z();
}

// Virtual
void ARasterizer::clear(const Eigen::Vector3f &color) {
    for (uint32_t row = 0; row < height(); row++) {
        for (uint32_t col = 0; col < width(); col++) {
            set_pixel(row, col, color);
        }
    }
}

ARasterizer::~ARasterizer() {
    delete[] pixel_data_;
}