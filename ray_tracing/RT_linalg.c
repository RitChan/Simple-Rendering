/**
 * @file RT_linalg.c
 * @author Hao CHEN
 * @brief Implementation of RT_linalg.h
 */

#include "RT_linalg.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "RT_struct.h"

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
    float scalar = 1 / norm_vec2f(vec);
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
    float scalar = 1 / norm_vec3f(vec);
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

void float_vec4f_inplace(float c, RT_Vec4f *vec) {
    vec->x = c * vec->x;
    vec->y = c * vec->y;
    vec->z = c * vec->z;
    vec->w = c * vec->w;
}

float vec4f_dot_vec4f(const RT_Vec4f *v0, const RT_Vec4f *v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z + v0->w * v1->w;
}

RT_Mat3f float_mat3f(float c, const RT_Mat3f *mat) {
    RT_Mat3f result;
    result.m00 = c * mat->m00;
    result.m01 = c * mat->m01;
    result.m02 = c * mat->m02;
    result.m10 = c * mat->m10;
    result.m11 = c * mat->m11;
    result.m12 = c * mat->m12;
    result.m20 = c * mat->m20;
    result.m21 = c * mat->m21;
    result.m22 = c * mat->m22;
    return result;
}

void float_mat3f_inplace(float c, RT_Mat3f *mat) {
    mat->m00 = c * mat->m00;
    mat->m01 = c * mat->m01;
    mat->m02 = c * mat->m02;
    mat->m10 = c * mat->m10;
    mat->m11 = c * mat->m11;
    mat->m12 = c * mat->m12;
    mat->m20 = c * mat->m20;
    mat->m21 = c * mat->m21;
    mat->m22 = c * mat->m22;
}

RT_Mat3f mat3f_mat3f(const RT_Mat3f *mat0, const RT_Mat3f *mat1) {
    RT_Mat3f result;
    result.m00 =
        mat0->m00 * mat1->m00 + mat0->m01 * mat1->m10 + mat0->m02 * mat1->m20;
    result.m01 =
        mat0->m00 * mat1->m01 + mat0->m01 * mat1->m11 + mat0->m02 * mat1->m21;
    result.m02 =
        mat0->m00 * mat1->m02 + mat0->m01 * mat1->m12 + mat0->m02 * mat1->m22;
    result.m10 =
        mat0->m10 * mat1->m00 + mat0->m11 * mat1->m10 + mat0->m12 * mat1->m20;
    result.m11 =
        mat0->m10 * mat1->m01 + mat0->m11 * mat1->m11 + mat0->m12 * mat1->m21;
    result.m12 =
        mat0->m10 * mat1->m02 + mat0->m11 * mat1->m12 + mat0->m12 * mat1->m22;
    result.m20 =
        mat0->m20 * mat1->m00 + mat0->m21 * mat1->m10 + mat0->m22 * mat1->m20;
    result.m21 =
        mat0->m20 * mat1->m01 + mat0->m21 * mat1->m11 + mat0->m22 * mat1->m21;
    result.m22 =
        mat0->m20 * mat1->m02 + mat0->m21 * mat1->m12 + mat0->m22 * mat1->m22;
    return result;
}

float det_mat3f(const RT_Mat3f *mat) {
    return mat->m00 * (mat->m11 * mat->m22 - mat->m12 * mat->m21) +
           (-mat->m10) * (mat->m01 * mat->m22 - mat->m02 * mat->m21) +
           mat->m20 * (mat->m01 * mat->m12 - mat->m02 * mat->m11);
}
