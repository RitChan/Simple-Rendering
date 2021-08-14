// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.
#include "core/Factory.h"

#include <list>

#include "core/Controller.h"
#include "core/VertexShader.h"

RenderController create_controller(ARasterizer &rasterizer) {
    RenderController result{};
    result.rasterizer_ = &rasterizer;
    result.vshaders_ = std::list<IShader *>{};
    return result;
}
