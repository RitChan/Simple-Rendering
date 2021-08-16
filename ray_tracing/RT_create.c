/**
 * @file RT_create.c
 * @author Hao CHEN
 * @brief Implementation of RT_create.h
 */

#include "RT_create.h"

RT_Mat3f create_mat3f(float a, float b, float c, float d, float e, float f,
                      float g, float h, float i) {
    RT_Mat3f result;
    result.m00 = a;
    result.m01 = b;
    result.m02 = c;
    result.m10 = d;
    result.m11 = e;
    result.m12 = f;
    result.m20 = g;
    result.m21 = h;
    result.m22 = i;
    return result;
}
