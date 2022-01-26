#include "shader_impl/MipmapShader.h"

IPrimitive &MipmapShader::current_primitive() {
    Eigen::Vector3i &v_idx = indices_.at(index_);
    auto v0 = transform_point_w(model_to_screen_, vertices_.at(v_idx.x()));
    auto v1 = transform_point_w(model_to_screen_, vertices_.at(v_idx.y()));
    auto v2 = transform_point_w(model_to_screen_, vertices_.at(v_idx.z()));
    triangle_.w_ = Eigen::Vector3f(v0.w(), v1.w(), v2.w());
    triangle_.w_inv_ = Eigen::Vector3f(1 / v0.w(), 1 / v1.w(), 1 / v2.w());
    triangle_.v0_ =
        Eigen::Vector3f(v0.x(), v0.y(), v0.z()) * triangle_.w_inv_[0];
    triangle_.v1_ =
        Eigen::Vector3f(v1.x(), v1.y(), v1.z()) * triangle_.w_inv_[1];
    triangle_.v2_ =
        Eigen::Vector3f(v2.x(), v2.y(), v2.z()) * triangle_.w_inv_[2];
    triangle_.uv0_ = uv_.at(v_idx.x());
    triangle_.uv1_ = uv_.at(v_idx.y());
    triangle_.uv2_ = uv_.at(v_idx.z());
    triangle_.texture_ = texture_;
    triangle_.mipmap_ = mipmap_;
    triangle_.mipmap_level_ = mipmap_level_;
    triangle_.set_cursor(triangle_.v0_.x(), triangle_.v0_.y());
    return triangle_;
}

uint32_t MipmapShader::set_texture_with_mipmap(BilinearTexture &tex,
                                               uint32_t mipmap_level) {
    texture_ = &tex;
    mipmap_level_ = mipmap_level;
    mipmap_ = new BilinearTexture[mipmap_level + 1];
    mipmap_image_ = new cv::Mat[mipmap_level + 1];
    mipmap_[0] = tex;
    mipmap_image_[0] = *tex.image_;
    for (uint32_t i = 1; i <= mipmap_level; i++) {
        float width_f = mipmap_image_[i - 1].cols / 2.f;
        float height_f = mipmap_image_[i - 1].rows / 2.f;
        int width = (int)width_f;
        int height = (int)height_f;
        if (width <= 0 || height <= 0) {
            mipmap_level_ = i - 1;
            break;
        }
        mipmap_[i] = BilinearTexture();
        mipmap_image_[i] = cv::Mat();
        cv::resize(*tex.image_, mipmap_image_[i], {width, height}, 0, 0,
                   cv::INTER_AREA);
        mipmap_[i].image_ = &mipmap_image_[i];
    }
    return mipmap_level_;
}
