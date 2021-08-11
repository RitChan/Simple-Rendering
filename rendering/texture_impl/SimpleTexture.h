// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_TEXTURE_IMPL_SIMPLE_TEXTURE_H
#define RENDERING_TEXTURE_IMPL_SIMPLE_TEXTURE_H

#include "core/Color.h"
#include "core/Texture.h"
#include "opencv2/opencv.hpp"

class SimpleTexture : public ITexture {
   public:
    Eigen::Vector3f sample(float u, float v) const override;

    cv::Mat *image_{nullptr};
};

#endif  // RENDERING_TEXTURE_IMPL_SIMPLE_TEXTURE_H
