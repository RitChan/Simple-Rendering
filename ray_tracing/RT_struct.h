/**
 * @file RT_structure
 * @author Hao CHEN
 * @brief all structures for ray tracing
 */

#ifndef RT_STRUCTURE_H
#define RT_STRUCTURE_H
struct vec2f {
    float x;
    float y;
};

struct vec3f {
    float x;
    float y;
    float z;
};

struct vec4f {
    float x;
    float y;
    float z;
    float w;
};

struct mat3f {
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

struct mat4f {
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

struct ray {
    struct vec3f origin;
    struct vec3f direction;
};

typedef struct vec2f RT_Vec2f;
typedef struct vec3f RT_Vec3f;
typedef struct vec4f RT_Vec4f;
typedef struct mat3f RT_Mat3f;
typedef struct mat4f RT_Mat4f;
typedef struct ray RT_Ray;
#endif  // RT_STRUCTURE_H
