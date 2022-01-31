#include "framework/GeneralPrimitive.h"

#include "core/Geometry.h"

[[nodiscard]] BoundingBox GeneralTriangle::get_bbox() const {
    BoundingBox result;
    result.left_ = std::fmin(v2_.x(), std::fmin(v0_.x(), v1_.x()));
    result.right_ = std::fmax(v2_.x(), std::fmax(v0_.x(), v1_.x()));
    result.bottom_ = std::fmin(v2_.y(), std::fmin(v0_.y(), v1_.y()));
    result.top_ = std::fmax(v2_.y(), std::fmax(v0_.y(), v1_.y()));
    return result;
}

bool is_inside_triangle_default(IPrimitive *primitive) {
    GeneralTriangle *tri = (GeneralTriangle *)primitive;
    return tri->alpha_ > 0 && tri->beta_ > 0 && tri->gamma_ > 0;
}

float interpolated_z_triangle_default(IPrimitive *primitive) {
    GeneralTriangle *tri = (GeneralTriangle *)primitive;
    return tri->alpha_ * tri->v0_.z() + tri->beta_ * tri->v1_.z() +
           tri->gamma_ * tri->v2_.z();
}

Eigen::Vector3f fragment_shader_default(IPrimitive *primitive) {
    return Eigen::Vector3f::Zero();
}

void set_cursor_triangle_default(IPrimitive *primitive, float x, float y) {
    GeneralTriangle *tri = (GeneralTriangle *)primitive;
    Eigen::Vector3f out;
    Eigen::Vector3f out_uv;
    calculate_barycentric(x, y, tri->v0_, tri->v1_, tri->v2_, tri->w_inv_, out,
                          out_uv);
    tri->alpha_ = out.x();
    tri->beta_ = out.y();
    tri->gamma_ = out.z();
    tri->alpha_uv_ = out_uv.x();
    tri->beta_uv_ = out_uv.y();
    tri->gamma_uv_ = out_uv.z();
}
