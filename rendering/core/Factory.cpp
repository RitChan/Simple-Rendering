// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#include "core/Factory.h"

#include <list>

#include "core/Controller.h"
#include "core/Shader.h"

RenderController create_controller(ARasterizer &rasterizer) {
    RenderController result{};
    result.rasterizer_ = &rasterizer;
    result.shaders_ = std::list<IShader *>{};
    return result;
}
