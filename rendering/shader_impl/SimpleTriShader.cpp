// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "shader_impl/SimpleTriShader.h"

#include <eigen3/Eigen/Eigen>

#include "core/Geometry.h"

IPrimitive &SimpleTriShader::current_primitive() {
    Eigen::Vector3i &v_idx = indices_.at(index_);
    primitive_->set_v0(
        transform_point(model_2_screen_, vertices_.at(v_idx.x())));
    primitive_->set_v1(
        transform_point(model_2_screen_, vertices_.at(v_idx.y())));
    primitive_->set_v2(
        transform_point(model_2_screen_, vertices_.at(v_idx.z())));
    primitive_->set_color0(colors_.at(v_idx.x()));
    primitive_->set_color1(colors_.at(v_idx.y()));
    primitive_->set_color2(colors_.at(v_idx.z()));
    return *primitive_;
}
