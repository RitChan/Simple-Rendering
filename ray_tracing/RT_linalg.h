/**
 * @file RT_linalg.h
 * @author Hao CHEN
 * @brief Linear algebra utilities
 */

#ifndef RT_LINALG_H
#define RT_LINALG_H
#include "RT_struct.h"

// Vec2f operations
RT_Vec2f float_vec2f(float c, const RT_Vec2f *vec);
float vec2f_dot_vec2f(const RT_Vec2f *v0, const RT_Vec2f *v1);
float norm_vec2f(const RT_Vec2f *vec);
float squared_norm_vec2f(const RT_Vec2f *vec);
float magnitude_vec2f(const RT_Vec2f *vec);
RT_Vec2f normalized_vec2f(const RT_Vec2f *vec);

// Vec3f operations
RT_Vec3f float_vec3f(float c, const RT_Vec3f *vec);
RT_Vec3f vec3f_cross_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1);
float vec3f_dot_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1);
float norm_vec3f(const RT_Vec3f *vec);
float squared_norm_vec3f(const RT_Vec3f *vec);
RT_Vec3f normalized_vec3f(const RT_Vec3f *vec);

// Vec4f operations
RT_Vec4f float_vec4f(float c, const RT_Vec4f *vec);
void float_vec4f_inplace(float c, RT_Vec4f *vec);
float vec4f_dot_vec4f(const RT_Vec4f *v0, const RT_Vec4f *v1);

// Mat3f operations
RT_Mat3f float_mat3f(float c, const RT_Mat3f *mat);
void float_mat3f_inplace(float c, RT_Mat3f *mat);
RT_Mat3f mat3f_mat3f(const RT_Mat3f *mat0, const RT_Mat3f *mat1);
RT_Mat3f inverse_mat3f(RT_Mat3f mat);  // Not implemented
float det_mat3f(const RT_Mat3f *mat);

// Mat4f operations
RT_Mat4f float_mat4f(float c, const RT_Mat4f *mat);
void float_mat4f_inplace(float c, const RT_Mat4f *mat);
RT_Mat4f mat4f_mat4f(const RT_Mat4f *mat0, const RT_Mat4f *mat1);
RT_Mat4f inverse_mat4f(RT_Mat4f mat);
float det_mat4f(const RT_Mat4f *mat);

// Matrix vector operations
RT_Vec3f transform_point(const RT_Mat4f *mat4, const RT_Vec3f *vec3);
RT_Vec3f transform_vector(const RT_Mat4f *mat4, const RT_Vec3f *vec3);
RT_Vec4f mat4_vec4(const RT_Mat4f *mat4, const RT_Vec4f *vec4);

#endif  // RT_LINALG_H
