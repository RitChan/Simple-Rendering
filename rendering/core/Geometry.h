// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_GEOMETRY_H
#define RENDERING_GEOMETRY_H

#include "Eigen/Eigen"

Eigen::Matrix4f create_view_matrix(Eigen::Vector3f camera_position, Eigen::Vector3f camera_forward,
                                   Eigen::Vector3f camera_up);

Eigen::Matrix4f create_perspective(float fov_radius, float aspect_ratio, float near_distance, float far_distance);


Eigen::Vector3f transform_point(Eigen::Matrix4f transform, Eigen::Vector3f point);
#endif //RENDERING_GEOMETRY_H
