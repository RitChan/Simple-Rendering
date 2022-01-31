#ifndef GENPRIMITIVE_H
#define GENPRIMITIVE_H

#include "core/Primitive.h"

typedef void (*FuncSetCursor)(IPrimitive *, float, float);
typedef bool (*FuncIsInside)(IPrimitive *);
typedef float (*FuncInterpolatedZ)(IPrimitive *);
typedef Eigen::Vector3f (*FuncFragmentShader)(IPrimitive *);

Eigen::Vector3f fragment_shader_default(IPrimitive *primitive);
void set_cursor_triangle_default(IPrimitive *primitive, float x, float y);
bool is_inside_triangle_default(IPrimitive *primitive);
float interpolated_z_triangle_default(IPrimitive *primitive);

class GeneralTriangle : public IPrimitive {
   public:
    [[nodiscard]] virtual BoundingBox get_bbox() const override;
    virtual void set_cursor(float x, float y) {
        (*set_cursor_triangle_)(this, x, y);
    }
    [[nodiscard]] virtual float interpolated_z() const {
        return (*interpolated_z_triangle_)((IPrimitive *)this);
    }
    [[nodiscard]] virtual bool is_inside() const override {
        return (*is_inside_triangle_default)((IPrimitive *)this);
    }
    [[nodiscard]] virtual Eigen::Vector3f get_color() const override {
        return (*fragment_shader_)((IPrimitive *)this);
    }
    ~GeneralTriangle() = default;

    Eigen::Vector2f cursor_ = Eigen::Vector2f::Zero();
    Eigen::Vector3f v0_ = Eigen::Vector3f::Zero();
    Eigen::Vector3f v1_ = Eigen::Vector3f::Zero();
    Eigen::Vector3f v2_ = Eigen::Vector3f::Zero();
    Eigen::Vector3f w_inv_;
    float alpha_ = 0;
    float beta_ = 0;
    float gamma_ = 0;
    float alpha_uv_ = 0;
    float beta_uv_ = 0;
    float gamma_uv_ = 0;
    FuncSetCursor set_cursor_triangle_ = set_cursor_triangle_default;
    FuncIsInside is_insdie_triangle_ = is_inside_triangle_default;
    FuncInterpolatedZ interpolated_z_triangle_ =
        interpolated_z_triangle_default;
    FuncFragmentShader fragment_shader_ = fragment_shader_default;
    void *user_data_{nullptr};
};

#endif  // GENPRIMITIVE_H
