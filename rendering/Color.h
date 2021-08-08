// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_COLOR_H
#define RENDERING_COLOR_H
#include <cstdint>
#include "Eigen/Eigen"
#include <vector>

namespace Color {
    typedef Eigen::Vector3f Color;
    extern Color RED;
    extern Color GREEN;
    extern Color BLUE;
}

struct RGB {
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    explicit RGB(const Eigen::Vector3f &vector);
};

uint8_t to_color_uint8(float color);
#endif //RENDERING_COLOR_H
