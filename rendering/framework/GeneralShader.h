#ifndef GENERALSHADER_H
#define GENERALSHADER_H

#include "core/Primitive.h"
#include "core/Shader.h"
#include "core/TriangleMesh.h"
#include "eigen3/Eigen/Eigen"

typedef void (*FuncReset)(IShader *shader);
typedef IPrimitive &(*FuncVertexShader)(IShader *shader);

void reset_default(IShader *shader);
IPrimitive &vertex_shader_default(IShader *shader);

class GeneralShader : public IShader {
   public:
    virtual void reset() override {
        // called every frame
        (*reset_)(this);
    }

    virtual bool exhausted() const override { return true; }

    virtual void next() override{};

    virtual IPrimitive &current_primitive() override {
        return (*vertex_shader_)(this);
    }

    void *user_data_{nullptr};
    FuncVertexShader vertex_shader_{vertex_shader_default};
    FuncReset reset_{reset_default};
};

class GeneralTriangleShader : public GeneralShader {
   public:
    virtual bool exhausted() const override {
        if (mesh_ == nullptr) return true;
        return index_ >= int(mesh_->indices.size());
    }

    virtual void next() override { index_++; }

    TriangleMesh *mesh_{nullptr};

    int index_{0};
};

#endif  // GENERALSHADER_H
