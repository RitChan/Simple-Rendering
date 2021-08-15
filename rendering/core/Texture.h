// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_TEXTURE_H
#define RENDERING_CORE_TEXTURE_H

#include <eigen3/Eigen/Eigen>

class ITexture {
   public:
    virtual Eigen::Vector3f sample(float u, float v) const = 0;
    virtual ~ITexture() = default;
};

#endif  // RENDERING_CORE_TEXTURE_H