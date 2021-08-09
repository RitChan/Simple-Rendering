// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "SimpleTriangle.h"

#include "Eigen/Eigen"
#include "shader_impl/SimpleShader.h"

IShader *SimpleTriangle::get_shader() const {
    Eigen::Vector3f color = color0_ * alpha + color1_ * beta + color2_ * gamma;
    return new SimpleShader(color);
}

void SimpleTriangle::update_barycentric() {
    Eigen::Matrix3f m;
    m << v0_.x(), v1_.x(), v2_.x(), v0_.y(), v1_.y(), v2_.y(), 1, 1, 1;
    Eigen::Vector3f b(cursor_.x(), cursor_.y(), 1);
    Eigen::Vector3f barycentric = m.inverse() * b;
    alpha = barycentric.x();
    beta = barycentric.y();
    gamma = barycentric.z();
}
