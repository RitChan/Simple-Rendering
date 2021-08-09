// Created by Ritee
// Copyright (c) 2021 Ritee All rights reserved.

#ifndef RENDERING_COLLIDER_H
#define RENDERING_COLLIDER_H

#include <cstdint>

struct BoundingBox {
   public:
    int32_t left_ = 0;
    int32_t right_ = 0;
    int32_t top_ = 0;
    int32_t bottom_ = 0;

    BoundingBox() = default;

    BoundingBox(int32_t left, int32_t right, int32_t bottom, int32_t top)
        : left_(left), right_(right), bottom_(bottom), top_(top) {}
};

#endif  // RENDERING_COLLIDER_H
