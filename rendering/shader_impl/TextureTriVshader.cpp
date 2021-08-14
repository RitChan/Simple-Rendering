// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "shader_impl/TextureTriVshader.h"
#include "Eigen/Eigen"
#include "core/Geometry.h"
IPrimitive &TextureTriVshader::current_primitive() {
    Eigen::Vector3i &v_idx = indices_.at(index_);
    tex_tri_.v0_ = transform_point(model_to_screen_, vertices_.at(v_idx.x()));
    tex_tri_.v1_ = transform_point(model_to_screen_, vertices_.at(v_idx.y()));
    tex_tri_.v2_ = transform_point(model_to_screen_, vertices_.at(v_idx.z()));
    tex_tri_.uv0_ = uv_.at(v_idx.x());
    tex_tri_.uv1_ = uv_.at(v_idx.y());
    tex_tri_.uv2_ = uv_.at(v_idx.z());\
    tex_tri_.set_cursor(tex_tri_.v0_.x(), tex_tri_.v0_.y());
    tex_tri_.texture_ = texture_;
    return tex_tri_;
}
