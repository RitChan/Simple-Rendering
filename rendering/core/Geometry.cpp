// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "Geometry.h"
#include "Eigen/Eigen"
#include "Eigen/Geometry"

Eigen::Vector3f transform_point(const Eigen::Matrix4f& transform, const Eigen::Vector3f &point) {
    auto point4f = Eigen::Vector4f(point.x(), point.y(), point.z(), 1);
    auto result4f = transform * point4f;
    return {result4f.x() / result4f.w(), result4f.y() / result4f.w(), result4f.z() / result4f.w()};
}

Eigen::Matrix4f create_view_matrix(const Eigen::Vector3f &camera_position, const Eigen::Vector3f &camera_forward,
                                   const Eigen::Vector3f &camera_up) {
    Eigen::Matrix4f result_inv{};
    Eigen::Vector3f cam_z = camera_forward.normalized();
    Eigen::Vector3f cam_y = camera_up.normalized();
    Eigen::Vector3f cam_x = cam_y.cross(cam_z);
    result_inv << cam_x.x(), cam_y.x(), cam_z.x(), camera_position.x(),
        cam_x.y(), cam_y.y(), cam_z.y(), camera_position.y(),
        cam_x.z(), cam_y.z(), cam_z.z(), camera_position.z(),
        0, 0, 0, 1;
    return result_inv.inverse();
}
