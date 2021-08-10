// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_VERTEX_SHADER_H
#define RENDERING_CORE_VERTEX_SHADER_H
#include "core/Primitive.h"

class IVertexShader {
public:
    virtual void reset_index() = 0;
    virtual bool exhausted() = 0;
    virtual void next() = 0;
    virtual IPrimitive &current_primitive();
};

#endif // RENDERING_CORE_VERTEX_SHADER_H