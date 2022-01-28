#ifndef DEPTHSHADER_H
#define DEPTHSHADER_H

#include "core/Shader.h"
#include "core/Primitive.h"
#include "core/TriangleMesh.h"
#include "eigen3/Eigen/Eigen"

class MeshShader : public IShader {
   public:
    virtual void reset() override {
        // called every frame
        model2screen_ = (*viewport_) * (*project_) * (*view_) * model_mat_;
        model2view_ = (*view_) * model_mat_;
        index_ = 0;
    }

    virtual bool exhausted() const override {
        if (mesh_ == nullptr) return false;
        return index_ >= int(mesh_->indices.size());
    }

    virtual void next() override {
        index_ += 1;
    }

    virtual IPrimitive &current_primitive() override = 0;

    TriangleMesh *mesh_{nullptr};
    Eigen::Matrix4f model_mat_;
    Eigen::Matrix4f *view_{nullptr};
    Eigen::Matrix4f *project_{nullptr};
    Eigen::Matrix4f *viewport_{nullptr};

   protected:
    Eigen::Matrix4f model2screen_ = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f model2view_ = Eigen::Matrix4f::Identity();
    int index_ = 0;
};



#endif  // DEPTHSHADER_H
