// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SHADING_H
#define RENDERING_SHADING_H
#include <utility>

#include "Color.h"
#include "Eigen/Eigen"

class IShader {
   public:
    virtual Eigen::Vector3f get_color() const = 0;
    virtual ~IShader() = default;
};
#endif  // RENDERING_SHADING_H
