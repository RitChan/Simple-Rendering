// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SIMPLESHADER_H
#define RENDERING_SIMPLESHADER_H

#include "Eigen/Eigen"
#include "RenderingCore.h"

class SimpleShader : public IShader {
   public:
    explicit SimpleShader(Eigen::Vector3f color) : color_(std::move(color)) {}

    Eigen::Vector3f get_color() override { return color_; }

   private:
    Eigen::Vector3f color_;
};

#endif  // RENDERING_SIMPLESHADER_H
