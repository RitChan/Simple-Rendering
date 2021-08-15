// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "SimpleTriangle.h"

#include <eigen3/Eigen/Eigen>

void SimpleTriangle::update_barycentric() {
    Eigen::Matrix3f m;
    m << v0_.x(), v1_.x(), v2_.x(), v0_.y(), v1_.y(), v2_.y(), 1, 1, 1;
    Eigen::Vector3f b(cursor_.x(), cursor_.y(), 1);
    Eigen::Vector3f barycentric = m.inverse() * b;
    alpha = barycentric.x();
    beta = barycentric.y();
    gamma = barycentric.z();
}
