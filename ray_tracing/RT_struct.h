/**
 * @file RT_structure
 * @author Hao CHEN
 * @brief all structures for ray tracing
 */

#ifndef RT_STRUCTURE_H
#define RT_STRUCTURE_H
struct rt_vec2f {
    float x;
    float y;
};

struct rt_vec3f {
    float x;
    float y;
    float z;
};

struct rt_vec4f {
    float x;
    float y;
    float z;
    float w;
};

struct rt_mat3f {
    float m00;
    float m01;
    float m02;
    float m10;
    float m11;
    float m12;
    float m20;
    float m21;
    float m22;
};

struct rt_mat4f {
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float m30;
    float m31;
    float m32;
    float m33;
};

struct rt_ray {
    struct rt_vec3f origin;
    struct rt_vec3f direction;
};

union rt_attribute {
    struct rt_vec3f vertex;
    struct rt_vec3f normal;
    struct rt_vec2f uv;
    struct rt_vec3f rgb;
    struct rt_vec4f rgba;
    struct {
        uint32_t i0;
        uint32_t i1;
        uint32_t i2;
    } tri_indices;
};

typedef struct rt_vec2f RT_Vec2f;
typedef struct rt_vec3f RT_Vec3f;
typedef struct rt_vec4f RT_Vec4f;
typedef struct rt_mat3f RT_Mat3f;
typedef struct rt_mat4f RT_Mat4f;
typedef struct rt_ray RT_Ray;
typedef union rt_attribute RT_UAttribute
#endif  // RT_STRUCTURE_H
