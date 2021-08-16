/**
 * @file RT_create.h
 * @author Hao CHEN
 * @brief Functions to create struct, on stack or heap
 */

#ifndef RT_CREATE_H
#define RT_CREATE_H

#include "RT_struct.h"

RT_Mat3f create_mat3f(float a, float b, float c, float d, float e, float f,
                      float g, float h, float i);

#endif  // RT_CREATE_H
