/**
 * @file RT_linalg.h
 * @author Hao CHEN
 * @brief Linear algebra utilities
 */

#ifndef RT_LINALG_H
#define RT_LINALG_H
#include "RT_struct.h"

// Vec2f operations
RT_Vec2f RT_float_vec2f(float c, const RT_Vec2f *vec);
float RT_vec2f_dot_vec2f(const RT_Vec2f *v0, const RT_Vec2f *v1);
float RT_norm_vec2f(const RT_Vec2f *vec);
float RT_squared_norm_vec2f(const RT_Vec2f *vec);
float RT_magnitude_vec2f(const RT_Vec2f *vec);
RT_Vec2f RT_normalized_vec2f(const RT_Vec2f *vec);

// Vec3f operations
RT_Vec3f RT_float_vec3f(float c, const RT_Vec3f *vec);
RT_Vec3f RT_vec3f_cross_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1);
float RT_vec3f_dot_vec3f(const RT_Vec3f *v0, const RT_Vec3f *v1);
float RT_norm_vec3f(const RT_Vec3f *vec);
float RT_squared_norm_vec3f(const RT_Vec3f *vec);
RT_Vec3f RT_normalized_vec3f(const RT_Vec3f *vec);

// Vec4f operations
RT_Vec4f RT_float_vec4f(float c, const RT_Vec4f *vec);
void RT_float_vec4f_inplace(float c, RT_Vec4f *vec);
float RT_vec4f_dot_vec4f(const RT_Vec4f *v0, const RT_Vec4f *v1);

// Mat3f operations
RT_Mat3f RT_float_mat3f(float c, const RT_Mat3f *mat);
void RT_float_mat3f_inplace(float c, RT_Mat3f *mat);
RT_Mat3f RT_mat3f_mat3f(const RT_Mat3f *mat0, const RT_Mat3f *mat1);
RT_Mat3f RT_inverse_mat3f(RT_Mat3f mat);  // Not implemented
float RT_det_mat3f(const RT_Mat3f *mat);

// Mat4f operations
RT_Mat4f RT_float_mat4f(float c, const RT_Mat4f *mat);
void RT_float_mat4f_inplace(float c, RT_Mat4f *mat);
RT_Mat4f RT_mat4f_mat4f(const RT_Mat4f *mat0, const RT_Mat4f *mat1);
RT_Mat4f RT_inverse_mat4f(RT_Mat4f mat);  // Not implemented
float RT_det_mat4f(const RT_Mat4f *mat);  // Not implemented

// Matrix vector operations
RT_Vec3f RT_transform_point(const RT_Mat4f *mat4, const RT_Vec3f *vec3);
RT_Vec3f RT_transform_vector(const RT_Mat4f *mat4, const RT_Vec3f *vec3);
RT_Vec4f RT_mat4_vec4(const RT_Mat4f *mat4, const RT_Vec4f *vec4);

#endif  // RT_LINALG_H
