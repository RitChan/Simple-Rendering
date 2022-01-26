#ifndef MIPMAPSHADER_H
#define MIPMAPSHADER_H

#include <vector>

#include "core/Shader.h"
#include "core/Texture.h"
#include "primitive_impl/MipmapTriangle.h"
#include "texture_impl/BilinearTexture.h"

class MipmapShader : public IShader {
   public:
    IPrimitive &current_primitive() override;

    bool exhausted() const override { return index_ >= tri_count(); }

    void next() override { index_++; }

    void reset() override {
        model_to_screen_ = (*viewport_) * (*projection_) * (*view_) * model_;
        index_ = 0;
    }

    uint32_t tri_count() const { return indices_.size(); }

    ~MipmapShader() {
        delete[] mipmap_;
        delete[] mipmap_image_;
    }

    uint32_t set_texture_with_mipmap(BilinearTexture &tex,
                                     uint32_t mipmap_level);

    void enable_uv_cache(uint32_t width, uint32_t height) {
        uv_cache_ = Eigen::MatrixXf(width, height);
    }

    std::vector<Eigen::Vector3f> vertices_;
    std::vector<Eigen::Vector3f> colors_;
    std::vector<Eigen::Vector2f> uv_;
    std::vector<Eigen::Vector3i> indices_;
    Eigen::Matrix4f model_;
    Eigen::Matrix4f *view_{nullptr};
    Eigen::Matrix4f *projection_{nullptr};
    Eigen::Matrix4f *viewport_{nullptr};
    BilinearTexture *texture_{nullptr};

   private:
    uint32_t index_;
    Eigen::Matrix4f model_to_screen_;
    BilinearTexture *mipmap_{nullptr};
    cv::Mat *mipmap_image_{nullptr};
    uint32_t mipmap_level_{0};
    MipmapTriangle triangle_;
    Eigen::MatrixXf uv_cache_;
};

#endif  // MIPMAPSHADER_H
