#include <cmath>
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <list>

#include "RenderingCore.h"
#include "framework/GeneralPrimitive.h"
#include "framework/GeneralShader.h"
#include "rasterizer_impl/SimpleRasterizer.h"

struct PrimitiveData {
    Eigen::Vector3f color;
};

struct ShaderData {
    Eigen::Matrix4f model_mat;
    Eigen::Matrix4f *view = nullptr;
    Eigen::Matrix4f *project = nullptr;
    Eigen::Matrix4f *viewport = nullptr;
    Eigen::Matrix4f model2screen = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f model2view = Eigen::Matrix4f::Identity();
    GeneralTriangle triangle;
    PrimitiveData *primitive_data = nullptr;
};

void shader_reset(IShader *i_shader) {
    // called every frame
    auto *tri_shader = (GeneralTriangleShader *)i_shader;
    auto *data = (ShaderData *)tri_shader->user_data_;
    data->model2view = (*data->view) * data->model_mat;
    data->model2screen =
        (*data->viewport) * (*data->project) * data->model2view;
    tri_shader->index_ = 0;
}

IPrimitive &vertex_shader(IShader *i_shader) {
    auto *tri_shader = (GeneralTriangleShader *)i_shader;
    auto *mesh = tri_shader->mesh_;
    auto *shader_data = (ShaderData *)tri_shader->user_data_;
    auto &tri = shader_data->triangle;
    auto idx = mesh->indices.at(tri_shader->index_);
    auto v0 =
        transform_point_w(shader_data->model2screen, mesh->vertices.at(idx[0]));
    auto v1 =
        transform_point_w(shader_data->model2screen, mesh->vertices.at(idx[1]));
    auto v2 =
        transform_point_w(shader_data->model2screen, mesh->vertices.at(idx[2]));
    tri.w_inv_ = Eigen::Vector3f(1 / v0.w(), 1 / v1.w(), 1 / v2.w());
    auto &w_inv = tri.w_inv_;
    tri.v0_ =
        Eigen::Vector3f(v0[0] * w_inv[0], v0[1] * w_inv[0], v0[2] * w_inv[0]);
    tri.v1_ =
        Eigen::Vector3f(v1[0] * w_inv[1], v1[1] * w_inv[1], v1[2] * w_inv[1]);
    tri.v2_ =
        Eigen::Vector3f(v2[0] * w_inv[2], v2[1] * w_inv[2], v2[2] * w_inv[2]);
    shader_data->primitive_data->color =
        Eigen::Vector3f(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX,
                        rand() / (float)RAND_MAX);
    tri.user_data_ = shader_data->primitive_data;
    return tri;
}

Eigen::Vector3f fragmen_shader(IPrimitive *primitive) {
    auto *tri = (GeneralTriangle *)primitive;
    auto *data = (PrimitiveData *)tri->user_data_;
    return data->color;
}

int main() {
    const uint32_t WIDTH = 600;
    const uint32_t HEIGHT = 400;
    GeneralTriangleShader shader;
    shader.reset_ = shader_reset;
    shader.vertex_shader_ = vertex_shader;
    auto mesh_list = std::list<TriangleMesh *>();
    bool loaded = load_obj_meshes("..\\..\\..\\resource\\ring.obj", mesh_list);
    if (!loaded) {
        std::cout << "Failed to load mesh" << std::endl;
        return -1;
    }
    shader.mesh_ = mesh_list.front();
    ShaderData shader_data;
    shader.user_data_ = &shader_data;
    shader_data.triangle.fragment_shader_ = fragmen_shader;
    auto view = create_view_matrix({0, 0, 30}, {0, 0, -1}, {0, 1, 0});
    auto proj =
        create_perspective(EIGEN_PI / 4, (float)WIDTH / HEIGHT, 0.1f, 100.f);
    auto viewport = create_viewport(WIDTH, HEIGHT);
    shader_data.view = &view;
    shader_data.project = &proj;
    shader_data.viewport = &viewport;
    auto model_mat = create_scale_matrix(50);
    model_mat = create_rotation_x(-EIGEN_PI / 4) * model_mat;
    model_mat = create_rotation_y(EIGEN_PI / 6) * model_mat;
    shader_data.model_mat = model_mat;
    PrimitiveData primitive_data;
    shader_data.primitive_data = &primitive_data;
    SimpleRasterizer rasterizer(WIDTH, HEIGHT);
    RenderController controller;
    controller.bg_color = COLOR_BLACK;
    controller.rasterizer_ = &rasterizer;
    auto shader_ptrs = std::list<IShader *>();
    controller.shader_ptrs_.push_back(&shader);
    controller.render_iamge();
    controller.show_image("Random Color");
    return 0;
}