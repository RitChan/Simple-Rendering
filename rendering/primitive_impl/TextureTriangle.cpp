// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "primitive_impl/TextureTriangle.h"

#include <eigen3/Eigen/Eigen>

[[nodiscard]] Eigen::Vector3f TextureTriangle::get_color() const {
    Eigen::Vector2f interpolated_uv = alpha * uv0_ + beta * uv1_ + gamma * uv2_;
    return texture_->sample(interpolated_uv.x(), interpolated_uv.y());
}

void TextureTriangle::update_barycentric() {
    Eigen::Matrix3f m;
    m << v0_.x(), v1_.x(), v2_.x(), v0_.y(), v1_.y(), v2_.y(), 1, 1, 1;
    Eigen::Vector3f b(cursor_.x(), cursor_.y(), 1);
    Eigen::Vector3f barycentric = m.inverse() * b;
    alpha = barycentric.x();
    beta = barycentric.y();
    gamma = barycentric.z();
}
