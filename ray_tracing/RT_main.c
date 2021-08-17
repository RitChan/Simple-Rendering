#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <gsl/gsl_matrix.h>
#include <stdio.h>

#include "RT.h"

void print_mat3f(const RT_Mat3f *mat) {
    printf("%-4.2f %-4.2f %-4.2f\n", mat->m00, mat->m01, mat->m02);
    printf("%-4.2f %-4.2f %-4.2f\n", mat->m10, mat->m11, mat->m12);
    printf("%-4.2f %-4.2f %-4.2f\n", mat->m20, mat->m21, mat->m22);
}

void print_vec3f(const RT_Vec3f *vec) {
    printf("%-4.5f %-4.5f %-4.2f\n", vec->x, vec->y, vec->z);
}

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    RT_Mat3f mat = create_mat3f(1, 0, 0, 0, 1, 0, 0, 0, 1);
    printf("%f\n", RT_det_mat3f(&mat));
    print_mat3f(&mat);
    RT_Vec3f vec = {9.0f, 5.0f, 7.0f};
    RT_Vec3f vec_norm_0 = RT_float_vec3f(1 / RT_norm_vec3f(&vec), &vec);
    RT_Vec3f vec_norm_1 = RT_normalized_vec3f(&vec);
    printf("%f\n", RT_norm_vec3f(&vec_norm_0));
    print_vec3f(&vec_norm_0);
    printf("%f\n", RT_norm_vec3f(&vec_norm_1));
    print_vec3f(&vec_norm_1);
    return 0;
}