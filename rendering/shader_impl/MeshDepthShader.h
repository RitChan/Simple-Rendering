#ifndef MESHDEPTHSHADER_H
#define MESHDEPTHSHADER_H
#include <iostream>

#include "primitive_impl/DepthTriangle.h"
#include "shader_impl/MeshShader.h"
#include "primitive_impl/NullPrimitive.h"

class MeshDepthShader : public MeshShader {
   public:
    IPrimitive &current_primitive() override;  // vertex shader

    virtual void reset() override {
        // called every frame
        MeshShader::reset();
    }

    void reset_obj_z_range() {
        obj_near_ = 1;
        obj_far_ = -1;
    }

    Eigen::Vector3f color_ = COLOR_WHITE;
    Eigen::Vector3f color_warning_ = COLOR_RED;
    float exp_ = 1;
    bool near_bright_ = true;
    bool bfc_ = false;
    bool ccw_ = true;  // "true" means removing ccw face
    float depth_norm_scalar_ = 1.5f;
    float barycentric_tolerance_ = 0.02;
    std::ostream *logger_{nullptr};

   private:
    float obj_near_ = -std::numeric_limits<float>::infinity();
    float obj_far_ = std::numeric_limits<float>::infinity();
    DepthTriangle triangle_;
    NullPrimitive null_primitive_;
};

#endif  // MESHDEPTHSHADER_H
