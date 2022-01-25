// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#include <ctime>
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

#include "RenderingCore.h"
#include "rasterizer_impl/SimpleRasterizer.h"
#include "shader_impl/TextureTriShader.h"
#include "texture_impl/BilinearTexture.h"

class RotationEvent : public ILoopEvent {
   public:
    TextureTriVshader *rotaion_obj{nullptr};
    float radius_per_second{0};

    virtual void start() {
        // Before the first frame
        last_frame = std::clock();
    }

    virtual void update() {
        // After every frame
        std::clock_t now = std::clock();
        long frame_interval_ms = 1000 * (now - last_frame) / CLOCKS_PER_SEC;
        float rotation_radius = frame_interval_ms * radius_per_second / 1000;
        rotaion_obj->model_ =
            create_rotation_y(rotation_radius) * rotaion_obj->model_;
        last_frame = now;
    }

   private:
    std::clock_t last_frame;
};

int main() {
    const uint32_t WIDTH = 600;
    const uint32_t HEIGHT = 400;
    const std::string IMG_PATH =
        "C:\\Users\\Ritee\\MyFiles\\r-project\\c-cpp\\rendering\\resource\\25."
        "png";
    cv::Mat image = cv::imread(IMG_PATH);
    cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    cv::flip(image, image, 0);
    int half_img_width = image.cols / 2;
    int half_img_height = image.rows / 2;
    float image_saclar = 1000.f;
    float canvas_half_width = half_img_width / image_saclar;
    float canvas_half_height = half_img_height / image_saclar;

    TextureTriVshader shader{};
    shader.vertices_ = std::vector<Eigen::Vector3f>{
        {-canvas_half_width, -canvas_half_height, 0},
        {canvas_half_width, -canvas_half_height, 0},
        {canvas_half_width, canvas_half_height, 0},
        {-canvas_half_width, canvas_half_height, 0}};
    shader.uv_ = std::vector<Eigen::Vector2f>{{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    shader.indices_ = std::vector<Eigen::Vector3i>{{0, 1, 2}, {0, 2, 3}};
    shader.model_ = create_model_matrix({0, 0, 0}, {0, 0, 1}, {0, 1, 0});
    auto view = create_view_matrix({0, 0, 4}, {0, 0, -1}, {0, 1, 0});
    auto project =
        create_perspective(M_PI_4, (float)WIDTH / (float)HEIGHT, 0.1f, 100.f);
    auto viewport = create_viewport(WIDTH, HEIGHT);
    shader.view_ = &view;
    shader.projection_ = &project;
    shader.viewport_ = &viewport;

    RotationEvent event;
    event.rotaion_obj = &shader;
    event.radius_per_second = M_PI_4;
    EventPool::instance().add_event(event);

    BilinearTexture texture{};
    texture.image_ = &image;
    shader.texture_ = &texture;

    SimpleRasterizer rasterizer = SimpleRasterizer(WIDTH, HEIGHT);
    RenderController controller{};
    controller.rasterizer_ = &rasterizer;
    controller.shader_ptrs_.push_back(&shader);

    controller.loop_forever("Kamisato Ayakas");
    return 0;
}