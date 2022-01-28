#include "shader_impl/MeshDepthShader.h"

#include "core/Geometry.h"
#include "primitive_impl/NullPrimitive.h"

IPrimitive &MeshDepthShader::current_primitive() {
    while (!exhausted()) {
        auto idx = mesh_->indices.at(index_);
        // normals
        const auto &n0 = mesh_->normals.at(idx[0]).normalized();
        const auto &n1 = mesh_->normals.at(idx[1]).normalized();
        const auto &n2 = mesh_->normals.at(idx[2]).normalized();
        if (bfc_) {
            Eigen::Vector3f avg_normal = (n0 + n1 + n2) / 3;
            avg_normal = transform_vector(model2view_, avg_normal);
            if (ccw_ && avg_normal.z() < 0) {
                next();
                continue;
            };
            if (!ccw_ && avg_normal.z() > 0) {
                next();
                continue;
            };
        }
        // configurations
        triangle_.color_ = color_;
        triangle_.color_warning_ = color_warning_;
        triangle_.exp_ = exp_;
        triangle_.near_bright_ = near_bright_;
        triangle_.bfc_ = bfc_;
        triangle_.ccw_ = ccw_;
        // view positions
        triangle_.view_n0_ = transform_vector(model2view_, n0);
        triangle_.view_n1_ = transform_vector(model2view_, n1);
        triangle_.view_n2_ = transform_vector(model2view_, n2);
        triangle_.obj_near_ = obj_near_;
        triangle_.obj_far_ = obj_far_;
        // screen positions
        const auto &v0 = mesh_->vertices.at(idx[0]);
        const auto &v1 = mesh_->vertices.at(idx[1]);
        const auto &v2 = mesh_->vertices.at(idx[2]);
        const auto &view_v0 = transform_point(model2view_, v0);
        const auto &view_v1 = transform_point(model2view_, v1);
        const auto &view_v2 = transform_point(model2view_, v2);
        float primitive_near_ =
            std::max(view_v0.z(), std::max(view_v1.z(), view_v2.z()));
        float primitive_far_ =
            std::min(view_v0.z(), std::min(view_v1.z(), view_v2.z()));
        obj_near_ = std::max(primitive_near_, obj_near_);
        obj_far_ = std::min(primitive_far_, obj_far_);
        triangle_.obj_near_ = obj_near_;
        triangle_.obj_far_ = obj_far_;
        triangle_.v0_ = transform_point(model2screen_, v0);
        triangle_.v1_ = transform_point(model2screen_, v1);
        triangle_.v2_ = transform_point(model2screen_, v2);
        auto &proj = *project_;
        triangle_.set_project_param(proj(2, 2), proj(2, 3));
        triangle_.depth_norm_scalar_ = depth_norm_scalar_;
        triangle_.logger_ = logger_;
        triangle_.barycentric_tolerance_ = barycentric_tolerance_;
        triangle_.set_cursor(0, 0);
        return triangle_;
    }
    return null_primitive_;
}
