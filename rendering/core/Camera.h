// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_CAMERA_H
#define RENDERING_CORE_CAMERA_H
#include "Eigen/Eigen"
#include "core/Geometry.h"

class Camera {
   public:
    Eigen::Vector3f position;
    Eigen::Vector3f forward;
    Eigen::Vector3f up;

    void move(Eigen::Vector3f displacement) { position += displacement; }

    Eigen::Matrix4f to_view() { create_view_matrix(position, forward, up); }
};

#endif  // RENDERING_CORE_CAMERA_H