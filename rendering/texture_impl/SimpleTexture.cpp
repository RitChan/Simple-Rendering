// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "texture_impl/SimpleTexture.h"
#include "Eigen/Eigen"

Eigen::Vector3f SimpleTexture::sample(float u, float v) const {
    if (u < 0.5 && v < 0.5) {
        printf("");
    }
    int col = (int)std::round(image_->cols * u) % image_->cols;
    int row = (int)std::round(image_->rows * v) % image_->rows;
    cv::Vec3b texel = image_->at<cv::Vec3b>(row, col);
    return Eigen::Vector3f{texel[0] / 255.f, texel[1] / 255.f, texel[2] / 255.f};
}
