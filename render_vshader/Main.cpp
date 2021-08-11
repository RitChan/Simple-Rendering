// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include <vector>

#include "Eigen/Eigen"
#include "RenderingCore.h"
#include "rasterizer_impl/SimpleRasterizer.h"
#include "vshader_impl/SimpleTriVshader.h"

class TransformEvent : public ILoopEvent {
   public:
    Eigen::Matrix4f projection_;
    Eigen::Matrix4f viewport_;
    Eigen::Matrix4f view_;
    Camera *cam_;

    TransformEvent() {
        projection_ = Eigen::Matrix4f::Identity();
        viewport_ = Eigen::Matrix4f::Identity();
    }

    void update() override { view_ = cam_->to_view(); }
};

int main() {
    uint32_t width = 600;
    uint32_t height = 400;

    SimpleTriVshader vshader{};
    // A triangle
    vshader.vertices_ =
        std::vector<Eigen::Vector3f>{{-1, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    vshader.colors_ =
        std::vector<Eigen::Vector3f>{COLOR_RED, COLOR_BLUE, COLOR_GREEN};
    vshader.indices_ = std::vector<Eigen::Vector3i>{{0, 1, 2}};

    Camera cam{};
    cam.position = Eigen::Vector3f{0, 0, 5};
    cam.forward = Eigen::Vector3f{0, 0, -1};
    cam.up = Eigen::Vector3f{0, 1, 0};

    TransformEvent t_event{};
    t_event.cam_ = &cam;
    t_event.view_ = cam.to_view();
    t_event.projection_ =
        create_perspective(M_PI_4, (float)width / (float)height, 0.1f, 100.f);
    t_event.viewport_ = create_viewport(width, height);
    EventPool::instance().add_event(t_event);

    vshader.projection_ = &t_event.projection_;
    vshader.view_ = &t_event.view_;
    vshader.viewport_ = &t_event.viewport_;
    vshader.model_ = create_model_matrix({0, 0, 0}, {0, 0, 1}, {0, 1, 0});

    SimpleRasterizer rasterizer{width, height};
    RenderController controller{};
    controller.rasterizer_ = &rasterizer;
    controller.vshaders_.push_back(&vshader);

    controller.loop_forever("Demo VShadr");
    return 0;
}