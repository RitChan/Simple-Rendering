// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "shader_impl/TextureTriShader.h"

#include <eigen3/Eigen/Eigen>

#include "core/Geometry.h"

IPrimitive &TextureTriVshader::current_primitive() {
    Eigen::Vector3i &v_idx = indices_.at(index_);
    auto v0 = transform_point_w(model_to_screen_, vertices_.at(v_idx.x()));
    auto v1 = transform_point_w(model_to_screen_, vertices_.at(v_idx.y()));
    auto v2 = transform_point_w(model_to_screen_, vertices_.at(v_idx.z()));
    tex_tri_.w_ = Eigen::Vector3f(v0.w(), v1.w(), v2.w());
    tex_tri_.w_inv_ = Eigen::Vector3f(1 / v0.w(), 1 / v1.w(), 1 / v2.w());
    tex_tri_.v0_ = Eigen::Vector3f(v0.x(), v0.y(), v0.z()) * tex_tri_.w_inv_[0];
    tex_tri_.v1_ = Eigen::Vector3f(v1.x(), v1.y(), v1.z()) * tex_tri_.w_inv_[1];
    tex_tri_.v2_ = Eigen::Vector3f(v2.x(), v2.y(), v2.z()) * tex_tri_.w_inv_[2];
    tex_tri_.uv0_ = uv_.at(v_idx.x());
    tex_tri_.uv1_ = uv_.at(v_idx.y());
    tex_tri_.uv2_ = uv_.at(v_idx.z());
    tex_tri_.set_cursor(tex_tri_.v0_.x(), tex_tri_.v0_.y());
    tex_tri_.texture_ = texture_;
    return tex_tri_;
}
