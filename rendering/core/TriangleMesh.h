// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_TRIANGLEMESH_H
#define RENDERING_TRIANGLEMESH_H
#include <eigen3/Eigen/Eigen>
#include <string>
#include <vector>

struct TriangleMesh {
   public:
    uint32_t triangle_count() const {
        if (indices.empty()) return vertices.size() / 3;
        return indices.size();
    }

    std::vector<Eigen::Vector3f> vertices;
    std::vector<Eigen::Vector2f> tex_uv;
    std::vector<Eigen::Vector3f> normals;
    std::vector<Eigen::Vector3f> colors;
    std::vector<Eigen::Vector3i> indices;
    Eigen::Matrix4f world_mat;
};

bool load_obj_meshes(const std::string &obj_path, std::list<TriangleMesh *> &out);
#endif  // RENDERING_TRIANGLEMESH_H
