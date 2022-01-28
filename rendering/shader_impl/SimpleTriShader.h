// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_SHADER_IMPL_SIMPLETRISHADER_H
#define RENDERING_SHADER_IMPL_SIMPLETRISHADER_H
#include <eigen3/Eigen/Eigen>
#include <vector>

#include "core/Primitive.h"
#include "core/Shader.h"

class ISimpleTriShaderProco : public IPrimitive {
   public:
    virtual void set_v0(Eigen::Vector3f v) = 0;
    virtual void set_v1(Eigen::Vector3f v) = 0;
    virtual void set_v2(Eigen::Vector3f v) = 0;
    virtual void set_color0(Eigen::Vector3f color) = 0;
    virtual void set_color1(Eigen::Vector3f color) = 0;
    virtual void set_color2(Eigen::Vector3f color) = 0;
};

class SimpleTriShader : public IShader {
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
    ISimpleTriShaderProco *primitive_;

   private:
    uint32_t index_ = 0;
    Eigen::Matrix4f model_2_screen_;
};

#endif  // RENDERING_SHADER_IMPL_SIMPLETRISHADER_H