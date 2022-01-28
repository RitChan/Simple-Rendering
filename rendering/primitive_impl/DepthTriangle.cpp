#include "primitive_impl/DepthTriangle.h"

#include <iostream>

#include "core/Geometry.h"

inline float __bounded_float(float f, float low, float hight);

void DepthTriangle::set_cursor(float x, float y) {
    cursor_ = Eigen::Vector2f(x, y);
    Eigen::Vector3f out;
    calculate_barycentric(x, y, v0_, v1_, v2_, out);
    alpha_ = out.x();
    beta_ = out.y();
    gamma_ = out.z();
}

[[nodiscard]] bool DepthTriangle::is_inside() const {
    if (alpha_ < -barycentric_tolerance_ || beta_ < -barycentric_tolerance_ ||
        gamma_ < -barycentric_tolerance_) {
        return false;
    }
    return true;
}

[[nodiscard]] Eigen::Vector3f DepthTriangle::get_color() const {
    float z = alpha_ * v0_.z() + beta_ * v1_.z() + gamma_ * v2_.z();
    if (z < -1 || z > 1) {
        return color_warning_;
    }
    if (std::abs(z - p22_) < 1e-3) {
        return color_warning_;
    }
    float view_z = p23_ / (z - p22_);
    float a;
    float near = std::min(obj_near_, view_near_);
    float far = std::max(obj_far_, view_far_);
    float depth_norm = std::abs(near - far) * depth_norm_scalar_;
    if (near_bright_) {
        a = std::abs(view_z - far) / depth_norm;
    } else {
        a = std::abs(near - view_z) / depth_norm;
    }
    Eigen::Vector3f result;
    result.x() = __bounded_float(std::pow(a * color_.x(), exp_), 0, 1);
    result.y() = __bounded_float(std::pow(a * color_.y(), exp_), 0, 1);
    result.z() = __bounded_float(std::pow(a * color_.z(), exp_), 0, 1);
    return result;
}

void DepthTriangle::set_project_param(float p22, float p23) {
    p22_ = p22;
    p23_ = p23;
    if (std::abs(p22 - 1) < 1e-3 || std::abs(p22 + 1) < 1e-3) {
        view_far_ = -1;
        view_near_ = 1;
    } else {
        view_far_ = p23 / (-1 - p22);
        view_near_ = p23 / (1 - p22);
    }
}

inline float __bounded_float(float f, float low, float hight) {
    return std::min(hight, std::max(low, f));
}
