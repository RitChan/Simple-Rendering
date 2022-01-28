// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include "Geometry.h"

#include <eigen3/Eigen/Eigen>

#include "core/Geometry.h"

Eigen::Vector3f transform_point(const Eigen::Matrix4f &transform,
                                const Eigen::Vector3f &point) {
    auto point4f = Eigen::Vector4f(point.x(), point.y(), point.z(), 1);
    auto result4f = transform * point4f;
    return {result4f.x() / result4f.w(), result4f.y() / result4f.w(),
            result4f.z() / result4f.w()};
}

Eigen::Vector4f transform_point_w(const Eigen::Matrix4f &transform,
                                  const Eigen::Vector3f &point) {
    auto point4f = Eigen::Vector4f(point.x(), point.y(), point.z(), 1);
    return transform * point4f;
}

Eigen::Vector3f transform_vector(const Eigen::Matrix4f &transform,
                                 const Eigen::Vector3f &vec) {
    auto vec4f = Eigen::Vector4f(vec.x(), vec.y(), vec.z(), 0);
    auto v = transform * vec4f;
    return Eigen::Vector3f(v[0], v[1], v[2]);
}

void calculate_barycentric(float x, float y, const Eigen::Vector3f &v0,
                           const Eigen::Vector3f &v1, const Eigen::Vector3f &v2,
                           const Eigen::Vector3f &w_inv, Eigen::Vector3f &out,
                           Eigen::Vector3f &out_uv) {
    Eigen::Matrix3f m;
    m << v0.x(), v1.x(), v2.x(), v0.y(), v1.y(), v2.y(), 1, 1, 1;
    Eigen::Vector3f b(x, y, 1);
    out = m.inverse() * b;
    float alpha_h = out.x() * w_inv[0];
    float beta_h = out.y() * w_inv[1];
    float gamma_h = out.z() * w_inv[2];
    float w = 1 / (alpha_h + beta_h + gamma_h);
    out_uv.x() = alpha_h * w;
    out_uv.y() = beta_h * w;
    out_uv.z() = gamma_h * w;
}

void calculate_barycentric(float x, float y, const Eigen::Vector3f &v0,
                           const Eigen::Vector3f &v1, const Eigen::Vector3f &v2,
                           Eigen::Vector3f &out) {
    Eigen::Matrix3f m;
    m << v0.x(), v1.x(), v2.x(), v0.y(), v1.y(), v2.y(), 1, 1, 1;
    Eigen::Vector3f b(x, y, 1);
    out = m.inverse() * b;
}

Eigen::Matrix4f create_view_matrix(const Eigen::Vector3f &camera_position,
                                   const Eigen::Vector3f &camera_forward,
                                   const Eigen::Vector3f &camera_up) {
    Eigen::Matrix4f result_inv{};
    Eigen::Vector3f cam_z = -camera_forward.normalized();
    Eigen::Vector3f cam_y = camera_up.normalized();
    Eigen::Vector3f cam_x = cam_y.cross(cam_z);
    cam_y = cam_z.cross(cam_x);
    result_inv << cam_x.x(), cam_y.x(), cam_z.x(), camera_position.x(),
        cam_x.y(), cam_y.y(), cam_z.y(), camera_position.y(), cam_x.z(),
        cam_y.z(), cam_z.z(), camera_position.z(), 0, 0, 0, 1;
    return result_inv.inverse();
}

Eigen::Matrix4f create_perspective(float fov_radius, float aspect_ratio,
                                   float near_distance, float far_distance) {
    float z_far = -far_distance;
    float z_near = -near_distance;
    float half_fov = fov_radius / 2;
    float height = -z_near * std::tan(half_fov) * 2;
    float width = height * aspect_ratio;

    Eigen::Matrix4f S;
    S << 2 / width, 0, 0, 0, 
        0, 2 / height, 0, 0, 
        0, 0, 2 / (z_near - z_far), 0,
        0, 0, 0, 1;

    Eigen::Matrix4f T;
    T << 1, 0, 0, 0, 
        0, 1, 0, 0, 
        0, 0, 1, -(z_near + z_far) / 2, 
        0, 0, 0, 1;

    Eigen::Matrix4f M;
    M << z_near, 0, 0, 0, 
        0, z_near, 0, 0, 
        0, 0, z_near + z_far, -z_near * z_far, 
        0, 0, 1, 0;

    return S * T * M;
}

Eigen::Matrix4f create_viewport(uint32_t width, uint32_t height) {
    Eigen::Matrix4f result;
    float half_width = (float)width / 2;
    float half_height = (float)height / 2;
    result << half_width, 0, 0, half_width, 0, half_height, 0, half_height, 0,
        0, 1, 0, 0, 0, 0, 1;
    return result;
}

Eigen::Matrix4f create_rotation_y(float radius) {
    float cos = std::cos(radius);
    float sin = std::sin(radius);
    Eigen::Matrix4f result;
    result << cos, 0, sin, 0, 0, 1, 0, 0, -sin, 0, cos, 0, 0, 0, 0, 1;
    return result;
}

Eigen::Matrix4f create_rotation_x(float radius) {
    float cos = std::cos(radius);
    float sin = std::sin(radius);
    Eigen::Matrix4f result;
    result << 1, 0, 0, 0, 0, cos, -sin, 0, 0, sin, cos, 0, 0, 0, 0, 1;
    return result;
}

Eigen::Matrix4f create_model_matrix(const Eigen::Vector3f &position,
                                    const Eigen::Vector3f &forward,
                                    const Eigen::Vector3f &up) {
    Eigen::Vector3f z = forward.normalized();
    Eigen::Vector3f y = up.normalized();
    Eigen::Vector3f x = y.cross(z);
    y = z.cross(x);
    Eigen::Matrix4f result;
    result << x.x(), y.x(), z.x(), position.x(), x.y(), y.y(), z.y(),
        position.y(), x.z(), y.z(), z.z(), position.z(), 0, 0, 0, 1;
    return result;
}

Eigen::Matrix4f create_scale_matrix(float s0, float s1, float s2) {
    Eigen::Matrix4f result;
    result << s0, 0, 0, 0, 0, s1, 0, 0, 0, 0, s2, 0, 0, 0, 0, 1;
    return result;
}

Eigen::Matrix4f create_scale_matrix(float s) {
    return create_scale_matrix(s, s, s);
}
