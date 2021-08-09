// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_PRIMITIVE_H
#define RENDERING_PRIMITIVE_H
#include "Collider.h"
#include "Eigen/Eigen"
#include "Shading.h"

class IPrimitive {
   public:
    [[nodiscard]] virtual BoundingBox get_bbox() const = 0;
    virtual void set_cursor(float x, float y) = 0;
    [[nodiscard]] virtual float interpolated_z() const = 0;
    [[nodiscard]] virtual bool is_inside() const = 0;
    [[nodiscard]] virtual IShader *get_shader() const = 0;
};

#endif  // RENDERING_PRIMITIVE_H
