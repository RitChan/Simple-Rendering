/**
 * @file RT_linalg.c
 * @author Hao CHEN
 * @brief Implementation of RT_linalg.h
 */

#include "RT_linalg.h"

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <xmmintrin.h>

#include "RT_struct.h"

RT_Vec2f RT_float_vec2f(float c, const RT_Vec2f *vec) {
    RT_Vec2f result;
    result.x = c * vec->x;
    result.y = c * vec->y;
    return result;
}

float RT_vec2f_dot_vec2f(const RT_Vec2f *v0, const RT_Vec2f *v1) {
    return v0->x * v1->x + v0->y + v0->x;
}

float RT_norm_vec2f(const RT_Vec2f *vec) {
    return sqrtf(vec->x * vec->x + vec->y * vec->y);
}

float RT_squared_norm_vec2f(const RT_Vec2f *vec) {
    return vec->x * vec->x + vec->y * vec->y;
}

float RT_magnitude_vec2f(const RT_Vec2f *vec) {
    return vec->x * vec->x + vec->y * vec->y;
}

RT_Vec2f RT_normalized_vec2f(const RT_Vec2f *vec) {
    RT_Vec2f result;
    float scalar = 1 / RT_norm_vec2f(vec);
    result.x = scalar * vec->x;
    result.y = scalar * vec->y;
    return result;
}

RT_Vec3f RT_float_vec3f(float c, const RT_Vec3f *vec) {
    RT_Vec3f result;
    result.x = c * vec->x;
    result.y = c * vec->y;
    result.z = c * vec->z;
    return result;
}

RT_Vec3f RT_vec3f_cross_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1) {
    RT_Vec3f result;
    // x = y0 * z1 - z0 * y1
    result.x = v0->y * v1->z - v0->z * v1->y;
    // y = z0 * x1 - x0 * z1
    result.y = v0->z * v1->x - v0->x * v1->z;
    // z = x0 * y1 - y0 * x1
    result.z = v0->x * v1->y - v0->y * v1->x;
    return result;
}

float RT_vec3f_dot_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z;
}

float RT_norm_vec3f(const RT_Vec3f *vec) {
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

float RT_squared_norm_vec3f(const RT_Vec3f *vec) {
    return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

RT_Vec3f RT_normalized_vec3f(const RT_Vec3f *vec) {
    RT_Vec3f result;
    float scalar = 1 / RT_norm_vec3f(vec);
    result.x = scalar * vec->x;
    result.y = scalar * vec->y;
    result.z = scalar * vec->z;
    return result;
}

RT_Vec4f RT_float_vec4f(float c, const RT_Vec4f *vec) {
    RT_Vec4f result;
    result.x = c * vec->x;
    result.y = c * vec->y;
    result.z = c * vec->z;
    result.w = c * vec->w;
    return result;
}

void RT_float_vec4f_inplace(float c, RT_Vec4f *vec) {
    vec->x = c * vec->x;
    vec->y = c * vec->y;
    vec->z = c * vec->z;
    vec->w = c * vec->w;
}

float RT_vec4f_dot_vec4f(const RT_Vec4f *v0, const RT_Vec4f *v1) {
    return v0->x * v1->x + v0->y * v1->y + v0->z * v1->z + v0->w * v1->w;
}

RT_Mat3f RT_float_mat3f(float c, const RT_Mat3f *mat) {
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

void RT_float_mat3f_inplace(float c, RT_Mat3f *mat) {
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

RT_Mat3f RT_mat3f_mat3f(const RT_Mat3f *mat0, const RT_Mat3f *mat1) {
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

float RT_det_mat3f(const RT_Mat3f *mat) {
    return mat->m00 * (mat->m11 * mat->m22 - mat->m12 * mat->m21) +
           (-mat->m10) * (mat->m01 * mat->m22 - mat->m02 * mat->m21) +
           mat->m20 * (mat->m01 * mat->m12 - mat->m02 * mat->m11);
}

RT_Mat4f RT_float_mat4f(float c, const RT_Mat4f *mat) {
    RT_Mat4f result;
    result.m00 = c * mat->m00;
    result.m01 = c * mat->m01;
    result.m02 = c * mat->m02;
    result.m03 = c * mat->m03;
    result.m10 = c * mat->m10;
    result.m11 = c * mat->m11;
    result.m12 = c * mat->m12;
    result.m13 = c * mat->m13;
    result.m20 = c * mat->m20;
    result.m21 = c * mat->m21;
    result.m22 = c * mat->m22;
    result.m23 = c * mat->m23;
    result.m30 = c * mat->m30;
    result.m31 = c * mat->m31;
    result.m32 = c * mat->m32;
    result.m33 = c * mat->m33;
    return result;
}

void RT_float_mat4f_inplace(float c, RT_Mat4f *mat) {
    mat->m00 = c * mat->m00;
    mat->m01 = c * mat->m01;
    mat->m02 = c * mat->m02;
    mat->m03 = c * mat->m03;
    mat->m10 = c * mat->m10;
    mat->m11 = c * mat->m11;
    mat->m12 = c * mat->m12;
    mat->m13 = c * mat->m13;
    mat->m20 = c * mat->m20;
    mat->m21 = c * mat->m21;
    mat->m22 = c * mat->m22;
    mat->m23 = c * mat->m23;
    mat->m30 = c * mat->m30;
    mat->m31 = c * mat->m31;
    mat->m32 = c * mat->m32;
    mat->m33 = c * mat->m33;
}

RT_Mat4f RT_mat4f_mat4f(const RT_Mat4f *mat0, const RT_Mat4f *mat1) {
    RT_Mat4f result;
    result.m00 = mat0->m00 * mat1->m00 + mat0->m01 * mat1->m10 +
                 mat0->m02 * mat1->m20 + mat0->m03 * mat1->m30;
    result.m01 = mat0->m00 * mat1->m01 + mat0->m01 * mat1->m11 +
                 mat0->m02 * mat1->m21 + mat0->m03 * mat1->m31;
    result.m02 = mat0->m00 * mat1->m02 + mat0->m01 * mat1->m12 +
                 mat0->m02 * mat1->m22 + mat0->m03 * mat1->m32;
    result.m03 = mat0->m00 * mat1->m03 + mat0->m01 * mat1->m13 +
                 mat0->m02 * mat1->m23 + mat0->m03 * mat1->m33;
    result.m10 = mat0->m10 * mat1->m00 + mat0->m11 * mat1->m10 +
                 mat0->m12 * mat1->m20 + mat0->m13 * mat1->m30;
    result.m11 = mat0->m10 * mat1->m01 + mat0->m11 * mat1->m11 +
                 mat0->m12 * mat1->m21 + mat0->m13 * mat1->m31;
    result.m12 = mat0->m10 * mat1->m02 + mat0->m11 * mat1->m12 +
                 mat0->m12 * mat1->m22 + mat0->m13 * mat1->m32;
    result.m13 = mat0->m10 * mat1->m03 + mat0->m11 * mat1->m13 +
                 mat0->m12 * mat1->m23 + mat0->m13 * mat1->m33;
    result.m20 = mat0->m20 * mat1->m00 + mat0->m21 * mat1->m10 +
                 mat0->m22 * mat1->m20 + mat0->m23 * mat1->m30;
    result.m21 = mat0->m20 * mat1->m01 + mat0->m21 * mat1->m11 +
                 mat0->m22 * mat1->m21 + mat0->m23 * mat1->m31;
    result.m22 = mat0->m20 * mat1->m02 + mat0->m21 * mat1->m12 +
                 mat0->m22 * mat1->m22 + mat0->m23 * mat1->m32;
    result.m23 = mat0->m20 * mat1->m03 + mat0->m21 * mat1->m13 +
                 mat0->m22 * mat1->m23 + mat0->m23 * mat1->m33;
    result.m30 = mat0->m30 * mat1->m00 + mat0->m31 * mat1->m10 +
                 mat0->m32 * mat1->m20 + mat0->m33 * mat1->m30;
    result.m31 = mat0->m30 * mat1->m01 + mat0->m31 * mat1->m11 +
                 mat0->m32 * mat1->m21 + mat0->m33 * mat1->m31;
    result.m32 = mat0->m30 * mat1->m02 + mat0->m31 * mat1->m12 +
                 mat0->m32 * mat1->m22 + mat0->m33 * mat1->m32;
    result.m33 = mat0->m30 * mat1->m03 + mat0->m31 * mat1->m13 +
                 mat0->m32 * mat1->m23 + mat0->m33 * mat1->m33;
    return result;
}

RT_Vec3f RT_transform_point(const RT_Mat4f *mat4, const RT_Vec3f *vec3) {
    RT_Vec3f result;
    result.x = mat4->m00 * vec3->x + mat4->m01 * vec3->y + mat4->m02 * vec3->z +
               mat4->m03;
    result.y = mat4->m10 * vec3->x + mat4->m11 * vec3->y + mat4->m12 * vec3->z +
               mat4->m13;
    result.z = mat4->m20 * vec3->x + mat4->m21 * vec3->y + mat4->m22 * vec3->z +
               mat4->m23;
    float w = mat4->m30 * vec3->x + mat4->m31 * vec3->y + mat4->m32 * vec3->z +
              mat4->m33;
    if (fabsf(w) > FLT_EPSILON) {
        result.x /= w;
        result.y /= w;
        result.z /= w;
    }
    return result;
}

RT_Vec3f RT_transform_vector(const RT_Mat4f *mat4, const RT_Vec3f *vec3) {
    RT_Vec3f result;
    result.x = mat4->m00 * vec3->x + mat4->m01 * vec3->y + mat4->m02 * vec3->z;
    result.y = mat4->m10 * vec3->x + mat4->m11 * vec3->y + mat4->m12 * vec3->z;
    result.z = mat4->m20 * vec3->x + mat4->m21 * vec3->y + mat4->m22 * vec3->z;
    return result;
}

RT_Vec4f RT_mat4_vec4(const RT_Mat4f *mat4, const RT_Vec4f *vec4) {
    RT_Vec4f result;
    result.x = mat4->m00 * vec4->x + mat4->m01 * vec4->y + mat4->m02 * vec4->z +
               vec4->w * mat4->m03;
    result.y = mat4->m10 * vec4->x + mat4->m11 * vec4->y + mat4->m12 * vec4->z +
               vec4->w * mat4->m13;
    result.z = mat4->m20 * vec4->x + mat4->m21 * vec4->y + mat4->m22 * vec4->z +
               vec4->w * mat4->m23;
    result.w = mat4->m30 * vec4->x + mat4->m31 * vec4->y + mat4->m32 * vec4->z +
               vec4->w * mat4->m33;
    return result;
}
