#include "core/Controller.h"

#include <string>

#include "core/Color.h"
#include "core/Event.h"
#include "opencv2/opencv.hpp"
#define ESC 27

void RenderController::render_iamge() {
    for (auto vshader : vshaders_) {
        vshader->reset_index();
        while (!vshader->exhausted()) {
            rasterizer_->rasterize(vshader->current_primitive());
            vshader->next();
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
    cv::flip(img_mat, img_mat, 0);
    while (true) {
        rasterizer_->clear(COLOR_BLACK);
        EventPool::instance().update_all();
        for (auto vshader : vshaders_) {
            vshader->reset_index();
            while (!vshader->exhausted()) {
                rasterizer_->rasterize(vshader->current_primitive());
                vshader->next();
            }
        }
        cv::cvtColor(img_mat, img_mat, cv::COLOR_RGB2BGR);
        cv::imshow(win_name, img_mat);
        if (cv::waitKey(1) == ESC) break;
    }
}