/**
 * @file RT_assert.c
 * @author Hao CHEN
 * @brief Implementation of RT_assert.h
 */

#include "RT_assert.h"

#include <stdio.h>
#include <stdlib.h>

#define ASSERT_NOT_NULL_FAILED 0

void RT_assert_not_null(void *ptr, const char *message) {
    if (ptr == NULL) {
        printf("assert_not_null failed: %s\n", message);
        exit(ASSERT_NOT_NULL_FAILED);
    }
}
