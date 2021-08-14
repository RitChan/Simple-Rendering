// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SIMPLETRIANGLE_H
#define RENDERING_SIMPLETRIANGLE_H

#include <cmath>

#include "Eigen/Eigen"
#include "RenderingCore.h"
#include "shader_impl/SimpleTriShader.h"

class SimpleTriangle : public ISimpleTriShaderProco {
   public:
    [[nodiscard]] BoundingBox get_bbox() const override {
        BoundingBox result;
        result.left_ = std::fmin(v2_.x(), std::fmin(v0_.x(), v1_.x()));
        result.right_ = std::fmax(v2_.x(), std::fmax(v0_.x(), v1_.x()));
        result.bottom_ = std::fmin(v2_.y(), std::fmin(v0_.y(), v1_.y()));
        result.top_ = std::fmax(v2_.y(), std::fmax(v0_.y(), v1_.y()));
        return result;
    }

    void set_cursor(float x, float y) override {
        cursor_ = Eigen::Vector2f(x, y);
        update_barycentric();
    }

    [[nodiscard]] float interpolated_z() const override {
        return v0_.z() * alpha + v1_.z() * beta + v2_.z() * gamma;
    }

    [[nodiscard]] bool is_inside() const override {
        return alpha >= 0 && beta >= 0 && gamma >= 0;
    }

    [[nodiscard]] Eigen::Vector3f get_color() const override {
        return alpha * color0_ + beta * color1_ + gamma * color2_;
    }

    void set_v0(Eigen::Vector3f v) override { v0_ = std::move(v); }
    void set_v1(Eigen::Vector3f v) override { v1_ = std::move(v); }
    void set_v2(Eigen::Vector3f v) override { v2_ = std::move(v); }
    void set_color0(Eigen::Vector3f color) override { color0_ = std::move(color); }
    void set_color1(Eigen::Vector3f color) override { color1_ = std::move(color); }
    void set_color2(Eigen::Vector3f color) override { color2_ = std::move(color); }

    Eigen::Vector3f v0_;
    Eigen::Vector3f v1_;
    Eigen::Vector3f v2_;
    Eigen::Vector3f color0_;
    Eigen::Vector3f color1_;
    Eigen::Vector3f color2_;

   protected:
    void update_barycentric();

    Eigen::Vector2f cursor_;
    float alpha;
    float beta;
    float gamma;
};

#endif  // RENDERING_SIMPLETRIANGLE_H
