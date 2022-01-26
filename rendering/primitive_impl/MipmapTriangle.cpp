#include "primitive_impl/MipmapTriangle.h"

void MipmapTriangle::set_cursor(float x, float y) {
    cursor_ = Eigen::Vector2f(x, y);
    Eigen::Vector3f out;
    Eigen::Vector3f out_uv;
    calculate_barycentric(x, y, v0_, v1_, v2_, w_inv_, out, out_uv);
    alpha_ = out.x();
    beta_ = out.y();
    gamma_ = out.z();
    alpha_uv_ = out_uv.x();
    beta_uv_ = out_uv.y();
    gamma_uv_ = out_uv.z();
    Eigen::Vector2f xy_uv =
        alpha_uv_ * uv0_ + beta_uv_ * uv1_ + gamma_uv_ * uv2_;
    calculate_barycentric(x + 0.001, y, v0_, v1_, v2_, w_inv_, out, out_uv);
    Eigen::Vector2f x1y_uv = out_uv.x() * uv0_ + out_uv.y() * uv1_ + out_uv.z() * uv2_;
    calculate_barycentric(x, y + 0.001, v0_, v1_, v2_, w_inv_, out, out_uv);
    Eigen::Vector2f xy1_uv = out_uv.x() * uv0_ + out_uv.y() * uv1_ + out_uv.z() * uv2_;
    int tex_width = texture_->image_->cols;
    int tex_height = texture_->image_->rows;
    du_dx_ = (x1y_uv.x() - xy_uv.x()) * tex_width * 1000;
    du_dy_ = (xy1_uv.x() - xy_uv.x()) * tex_width * 1000;
    dv_dx_ = (x1y_uv.y()  - xy_uv.y()) * tex_height * 1000;
    dv_dy_ = (xy1_uv.y()  - xy_uv.y()) * tex_height * 1000;
}

[[nodiscard]] Eigen::Vector3f MipmapTriangle::get_color() const {
    auto uv = alpha_uv_ * uv0_ + beta_uv_ * uv1_ + gamma_uv_ * uv2_;
    if (mipmap_level_ == 0) {
        return texture_->sample(uv.x(), uv.y());
    }
    auto ds_dx = Eigen::Vector2f(du_dx_, dv_dx_);
    auto ds_dy = Eigen::Vector2f(du_dy_, dv_dy_);
    // footprint = texels per pixel
    float footprint_size = std::max(ds_dx.squaredNorm(), ds_dy.squaredNorm());
    float footprint = std::sqrt(footprint_size);
    if (footprint <= 1 + 1e-2) {
        return texture_->sample(uv.x(), uv.y());
    }
    float mipmap_level = std::log2(footprint);
    if (mipmap_level >= mipmap_level_) {
        return mipmap_[mipmap_level_].sample(uv.x(), uv.y());
    }
    int floor_level = (int)std::floor(mipmap_level);
    int ceil_level = floor_level + 1;
    auto sample_low = mipmap_[floor_level].sample(uv.x(), uv.y());
    auto sample_high = mipmap_[ceil_level].sample(uv.x(), uv.y());
    float a = mipmap_level - floor_level;
    return (1 - a) * sample_low + a * sample_high;
}
