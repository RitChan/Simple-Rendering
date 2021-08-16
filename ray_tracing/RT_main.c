#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <gsl/gsl_matrix.h>
#include "RT.h"


int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    return 0;
}