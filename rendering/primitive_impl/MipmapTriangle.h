#ifndef MIPMAPTRIANGLE_H
#define MIPMAPTRIANGLE_H

#include "core/Primitive.h"
#include "core/Geometry.h"
#include "texture_impl/BilinearTexture.h"

class MipmapTriangle : public IPrimitive {
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

    [[nodiscard]] bool is_inside() const override {
        return alpha_ >= 0 && beta_ >= 0 && gamma_ >= 0;
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
    BilinearTexture *texture_{nullptr};
    BilinearTexture *mipmap_{nullptr};
    uint32_t mipmap_level_{0};
    Eigen::MatrixXf *uv_cache_{nullptr};

   protected:
    Eigen::Vector2f cursor_;
    float alpha_;
    float beta_;
    float gamma_;
    float alpha_uv_;
    float beta_uv_;
    float gamma_uv_;
    float du_dx_;
    float du_dy_;
    float dv_dx_;
    float dv_dy_;
};

#endif  // MIPMAPTRIANGLE_H
