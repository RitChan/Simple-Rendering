// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "primitive_impl/TextureTriangle.h"

#include <eigen3/Eigen/Eigen>

[[nodiscard]] Eigen::Vector3f TextureTriangle::get_color() const {
    Eigen::Vector2f interpolated_uv = alpha_uv * uv0_ + beta_uv * uv1_ + gamma_uv * uv2_;
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
    float alpha_h = alpha * w_inv_[0];
    float beta_h = beta * w_inv_[1];
    float gamma_h = gamma * w_inv_[2];
    float w = 1 / (alpha_h + beta_h + gamma_h);
    alpha_uv = alpha_h * w;
    beta_uv = beta_h * w;
    gamma_uv = gamma_h * w;
}
