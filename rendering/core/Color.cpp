// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "Color.h"

#include "Eigen/Eigen"

Color COLOR_RED = Eigen::Vector3f(1, 0, 0);
Color COLOR_GREEN = Eigen::Vector3f(0, 1, 0);
Color COLOR_BLUE = Eigen::Vector3f(0, 0, 1);
Color COLOR_BLACK = Eigen::Vector3f(0, 0, 0);

RGB::RGB(const Eigen::Matrix<float, 3, 1> &vector) {
    r = to_color_uint8(vector.x());
    g = to_color_uint8(vector.y());
    b = to_color_uint8(vector.z());
}

uint8_t to_color_uint8(float color) {
    if (color < 0) return 0;
    if (color > 1) return 255;
    return 255 * color;
}
