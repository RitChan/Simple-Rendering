#include "core/Controller.h"

#include <opencv2/opencv.hpp>
#include <string>

#include "core/Color.h"
#include "core/Event.h"

#define ESC 27

void RenderController::render_iamge() {
    for (auto shader_ptr : shader_ptrs_) {
        shader_ptr->reset();
        while (!shader_ptr->exhausted()) {
            rasterizer_->rasterize(shader_ptr->current_primitive());
            shader_ptr->next();
        }
    }
}

void RenderController::show_image(const std::string &win_name) {
    cv::Mat img_mat = cv::Mat(rasterizer_->height(), rasterizer_->width(),
                              CV_32FC3, rasterizer_->data());
    cv::flip(img_mat, img_mat, 0);
    cv::imshow(win_name, img_mat);
    cv::waitKey();
}

void RenderController::loop_forever(const std::string &win_name) {
    EventPool::instance().start_all();
    cv::Mat img_mat = cv::Mat(rasterizer_->height(), rasterizer_->width(),
                              CV_32FC3, rasterizer_->data());
    auto last_tick = std::clock();
    while (true) {
        rasterizer_->clear(bg_color);
        for (auto shader_ptr : shader_ptrs_) {
            shader_ptr->reset();
            while (!shader_ptr->exhausted()) {
                rasterizer_->rasterize(shader_ptr->current_primitive());
                shader_ptr->next();
            }
        }
        EventPool::instance().update_all();
        cv::cvtColor(img_mat, img_mat, cv::COLOR_RGB2BGR);
        cv::flip(img_mat, img_mat, 0);
        cv::imshow(win_name, img_mat);
        if (cv::waitKey(1) == ESC) break;
        if (show_fps) {
            auto cur_tick = std::clock();
            auto diff_tick = cur_tick - last_tick;
            double frame_cost_ms = 1000 * diff_tick / CLOCKS_PER_SEC;
            last_tick = cur_tick;
            std::cout << "\rFPS = " << 1000 / frame_cost_ms; 
        }
    }
}