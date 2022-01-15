// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_GEOMETRY_H
#define RENDERING_GEOMETRY_H

#include <eigen3/Eigen/Eigen>

Eigen::Matrix4f create_rotation_y(float radius);

Eigen::Matrix4f create_model_matrix(const Eigen::Vector3f &position,
                                    const Eigen::Vector3f &forward,
                                    const Eigen::Vector3f &up);

Eigen::Matrix4f create_view_matrix(const Eigen::Vector3f &camera_position,
                                   const Eigen::Vector3f &camera_forward,
                                   const Eigen::Vector3f &camera_up);

Eigen::Matrix4f create_perspective(float fov_radius, float aspect_ratio,
                                   float near_distance, float far_distance);

Eigen::Matrix4f create_viewport(uint32_t width, uint32_t height);

Eigen::Vector3f transform_point(const Eigen::Matrix4f &transform,
                                const Eigen::Vector3f &point);

Eigen::Vector4f transform_point_w(const Eigen::Matrix4f &transform,
                                  const Eigen::Vector3f &point);

#endif  // RENDERING_GEOMETRY_H
