// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_CONTROLLER_H
#define RENDERING_CORE_CONTROLLER_H

#include "core/VertexShader.h"
#include "core/Rasterizer.h"

#include <list>
#include <string>


class RenderController {
public:
    std::list<IShader *> vshaders_{};
    ARasterizer *rasterizer_{nullptr};

    void render_iamge();

    void show_image(const std::string &win_name);

    virtual void loop_forever(const std::string &win_name);

    virtual ~RenderController() = default;
};


#endif // RENDERING_CORE_CONTROLLER_H
