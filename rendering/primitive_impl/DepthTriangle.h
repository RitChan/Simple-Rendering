#ifndef DEPTHTRIANGLE_H
#define DEPTHTRIANGLE_H

#include <iostream>

#include "core/Color.h"
#include "core/Primitive.h"

class DepthTriangle : public IPrimitive {
   public:
    [[nodiscard]] BoundingBox get_bbox() const override {
        BoundingBox result;
        result.left_ = std::fmin(v2_.x(), std::fmin(v0_.x(), v1_.x()));
        result.right_ = std::fmax(v2_.x(), std::fmax(v0_.x(), v1_.x()));
        result.bottom_ = std::fmin(v2_.y(), std::fmin(v0_.y(), v1_.y()));
        result.top_ = std::fmax(v2_.y(), std::fmax(v0_.y(), v1_.y()));
        return result;
    }
    void set_cursor(float x, float y) override;

    [[nodiscard]] float interpolated_z() const override {
        return v0_.z() * alpha_ + v1_.z() * beta_ + v2_.z() * gamma_;
    }

    [[nodiscard]] bool is_inside() const override;

    [[nodiscard]] virtual Eigen::Vector3f get_color() const;  // fragment shader

    void set_project_param(float p22, float p23);

    Eigen::Vector3f v0_;
    Eigen::Vector3f v1_;
    Eigen::Vector3f v2_;
    Eigen::Vector3f view_n0_;
    Eigen::Vector3f view_n1_;
    Eigen::Vector3f view_n2_;
    Eigen::Vector3f color_ = COLOR_WHITE;
    Eigen::Vector3f color_warning_ = COLOR_RED;
    float exp_ = 1;
    bool near_bright_ = true;
    bool bfc_ = false;
    bool ccw_ = false;
    float obj_near_ = -std::numeric_limits<float>::infinity();
    float obj_far_ = std::numeric_limits<float>::infinity();
    float depth_norm_scalar_ = 1.5;
    float barycentric_tolerance_ = 0.02;
    std::ostream *logger_{nullptr};

   private:
    Eigen::Vector2f cursor_;
    float alpha_ = -1.0f;
    float beta_ = -1.0f;
    float gamma_ = -1.0f;
    float p22_ = 0;
    float p23_ = 1;
    float view_near_ = 1;
    float view_far_ = -1;
};

#endif  // DEPTHTRIANGLE_H
