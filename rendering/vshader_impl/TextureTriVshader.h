// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_VSHADER_IMPL_TEXTURE_TRI_VSHADER_H
#define RENDERING_VSHADER_IMPL_TEXTURE_TRI_VSHADER_H

#include <vector>

#include "core/VertexShader.h"
#include "core/Texture.h"
#include "primitive_impl/TextureTriangle.h"

class TextureTriVshader : public IVertexShader {
   public:
    IPrimitive &current_primitive() override;

    bool exhausted() const override { return index_ >= tri_count(); }

    void next() override { index_++; }

    void reset() override {
        model_to_screen_ = (*viewport_) * (*projection_) * (*view_) * model_;
        index_ = 0;
    }

    uint32_t tri_count() const { return indices_.size(); }

    std::vector<Eigen::Vector3f> vertices_;
    std::vector<Eigen::Vector3f> colors_;
    std::vector<Eigen::Vector2f> uv_;
    std::vector<Eigen::Vector3i> indices_;
    Eigen::Matrix4f model_;
    Eigen::Matrix4f *view_{nullptr};
    Eigen::Matrix4f *projection_{nullptr};
    Eigen::Matrix4f *viewport_{nullptr};
    ITexture *texture_;

   private:
    uint32_t index_;
    Eigen::Matrix4f model_to_screen_;
    TextureTriangle tex_tri_;
};

#endif