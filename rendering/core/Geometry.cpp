// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "Geometry.h"
#include "Eigen/Eigen"

Eigen::Vector3f transform_point(Eigen::Matrix4f transform, Eigen::Vector3f point) {
    auto point4f = Eigen::Vector4f(point.x(), point.y(), point.z(), 1);
    auto result4f = transform * point4f;
    return Eigen::Vector3f(result4f.x(), result4f.y(), result4f.z());
}
