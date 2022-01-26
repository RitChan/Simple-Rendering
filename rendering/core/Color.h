// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_COLOR_H
#define RENDERING_COLOR_H
#include <cstdint>
#include <eigen3/Eigen/Eigen>
#include <vector>

typedef Eigen::Vector3f Color;
extern Color COLOR_RED;
extern Color COLOR_GREEN;
extern Color COLOR_BLUE;
extern Color COLOR_BLACK;
extern Color COLOR_WHITE;

struct RGB {
   public:
    uint8_t r;
    uint8_t g;
    uint8_t b;

    explicit RGB(const Eigen::Vector3f &vector);
};

uint8_t to_color_uint8(float color);
#endif  // RENDERING_COLOR_H
