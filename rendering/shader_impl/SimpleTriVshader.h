// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_VSHADER_IMPL_H
#define RENDERING_VSHADER_IMPL_H
#include <vector>

#include "Eigen/Eigen"
#include "core/Camera.h"
#include "core/VertexShader.h"
#include "primitive_impl/SimpleTriangle.h"

class SimpleTriVshader : public IShader {
   public:
    uint32_t tri_count() const { return indices_.size(); }

    IPrimitive &current_primitive() override;

    bool exhausted() const override { return index_ >= tri_count(); }

    void next() override { index_++; }

    void reset() override {
        model_2_screen_ = (*viewport_) * (*projection_) * (*view_) * model_;
        index_ = 0;
    }

    std::vector<Eigen::Vector3f> vertices_;
    std::vector<Eigen::Vector3f> colors_;
    std::vector<Eigen::Vector3i> indices_;
    Eigen::Matrix4f model_;
    Eigen::Matrix4f *view_{nullptr};
    Eigen::Matrix4f *projection_{nullptr};
    Eigen::Matrix4f *viewport_{nullptr};

   private:
    uint32_t index_ = 0;
    SimpleTriangle tri_{};
    Eigen::Matrix4f model_2_screen_;
    
};

#endif  // RENDERING_VSHADER_IMPL_H