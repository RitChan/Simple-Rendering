// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_CORE_SHADER_H
#define RENDERING_CORE_SHADER_H
#include "core/Primitive.h"

class IShader {
   public:
    virtual void reset() = 0;
    virtual bool exhausted() const = 0;
    virtual void next() = 0;
    virtual IPrimitive &current_primitive() = 0;
    virtual ~IShader() = default;
};

#endif  // RENDERING_CORE_SHADER_H