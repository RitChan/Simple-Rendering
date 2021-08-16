/**
 * @file RT_linalg.c
 * @author Hao CHEN
 * @brief Implementation of RT_linalg.h
 */

#include "RT_linalg.h"

#include <math.h>
#include <stdio.h>

#include "RT_struct.h"

/**
 * @see
 * https://github.com/id-Software/Quake-III-Arena/blob/master/code/game/q_math.c#L552
 * @copyright Copyright (C) 1999-2005 Id Software, Inc.
 */
static float Q_rsqrt(float number);

RT_Vec2f float_vec2f(float c, const RT_Vec2f *vec) {
    RT_Vec2f result;
    if (vec == NULL) {
        result.x = 0;
        result.y = 0;
        return result;
    }
    result.x = c * vec->x;
    result.y = c * vec->y;
    return result;
}

float vec2f_dot_vec2f(const RT_Vec2f *v0, const RT_Vec2f *v1) {
    return v0->x * v1->x + v0->y + v0->x;
}

float norm_vec2f(const RT_Vec2f *vec) {
    return sqrtf(vec->x * vec->x + vec->y * vec->y);
}

float squared_norm_vec2f(const RT_Vec2f *vec) {
    return vec->x * vec->x + vec->y * vec->y;
}

float magnitude_vec2f(const RT_Vec2f *vec) {
    return vec->x * vec->x + vec->y * vec->y;
}

RT_Vec2f normalized_vec2f(const RT_Vec2f *vec) {
    RT_Vec2f result;
    float scalar = Q_rsqrt(vec->x * vec->x + vec->y * vec->y);
    result.x = scalar * vec->x;
    result.y = scalar * vec->y;
    return result;
}

RT_Vec3f float_vec3f(float c, const RT_Vec3f *vec) {
    RT_Vec3f result;
    result.x = c * vec->x;
    result.y = c * vec->y;
    result.z = c * vec->z;
    return result;
}

RT_Vec3f vec3f_cross_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1) {
    RT_Vec3f result;
    // x = y0 * z1 - z0 * y1
    result.x = v0->y * v1->z - v0->z * v1->y;
    // y = z0 * x1 - x0 * z1
    result.y = v0->z * v1->x - v0->x * v1->z;
    // z = x0 * y1 - y0 * x1
    result.z = v0->x * v1->y - v0->y * v1->x;
    return result;
}

float vec3f_dot_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;
}

float norm_vec3f(const RT_Vec3f *vec) {
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

float squared_norm_vec3f(const RT_Vec3f *vec) {
    return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

RT_Vec3f normalized_vec3f(const RT_Vec3f *vec) {
    RT_Vec3f result;
    float scalar = Q_rsqrt(vec->x * vec->x + vec->y * vec->y + vec->z + vec->z);
    result.x = scalar * vec->x;
    result.y = scalar * vec->y;
    result.z = scalar * vec->z;
    return result;
}

RT_Vec4f float_vec4f(float c, const RT_Vec4f *vec) {
    RT_Vec4f result;
    result.x = c * vec->x;
    result.y = c * vec->y;
    result.z = c * vec->z;
    result.w = c * vec->w;
    return result;
}

float vec4f_dot_vec4f(const RT_Vec4f *v0, const RT_Vec4f *v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z + v0->w * v1->w;
}

static float Q_rsqrt(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;            // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1);  // what the fuck?
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));  // 1st iteration
    return y;
}
