// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "shader_impl/SimpleTriShader.h"
#include "core/Geometry.h"
#include "Eigen/Eigen"

IPrimitive &SimpleTriShader::current_primitive() {
    Eigen::Vector3i &v_idx = indices_.at(index_);
    tri_.v0_ = transform_point(model_2_screen_, vertices_.at(v_idx.x()));
    tri_.v1_ = transform_point(model_2_screen_, vertices_.at(v_idx.y()));
    tri_.v2_ = transform_point(model_2_screen_, vertices_.at(v_idx.z()));
    tri_.color0_ = colors_.at(v_idx.x());
    tri_.color1_ = colors_.at(v_idx.y());
    tri_.color2_ = colors_.at(v_idx.z());
    tri_.set_cursor(tri_.v0_.x(), tri_.v1_.y());
    return tri_;
}
