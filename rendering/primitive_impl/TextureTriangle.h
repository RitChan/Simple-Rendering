// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_PRIMITIVE_IMPL_TEXTURE_TRIANGLE_H
#define RENDERING_PRIMITIVE_IMPL_TEXTURE_TRIANGLE_H
#include "core/Primitive.h"
#include "core/Texture.h"

class TextureTriangle : public IPrimitive {
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

    [[nodiscard]] Eigen::Vector3f get_color() const override;

    Eigen::Vector3f v0_;
    Eigen::Vector3f v1_;
    Eigen::Vector3f v2_;
    Eigen::Vector2f uv0_;
    Eigen::Vector2f uv1_;
    Eigen::Vector2f uv2_;
    Eigen::Vector3f w_;
    Eigen::Vector3f w_inv_;
    ITexture *texture_;

   protected:
    void update_barycentric();

    Eigen::Vector2f cursor_;
    float alpha;
    float beta;
    float gamma;
    float alpha_uv;
    float beta_uv;
    float gamma_uv;
};

#endif