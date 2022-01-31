// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_CONTROLLER_H
#define RENDERING_CORE_CONTROLLER_H

#include "core/Shader.h"
#include "core/Rasterizer.h"

#include <list>
#include <string>


class RenderController {
public:
    std::list<IShader *> shader_ptrs_{};
    ARasterizer *rasterizer_{nullptr};

    void render_image();

    void show_image(const std::string &win_name);

    virtual void loop_forever(const std::string &win_name);

    virtual ~RenderController() = default;

    Eigen::Vector3f bg_color = COLOR_WHITE;
    bool show_fps_ = false;
    bool show_image_ = true;
};


#endif // RENDERING_CORE_CONTROLLER_H
