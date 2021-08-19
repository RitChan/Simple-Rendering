#ifndef DATA_H
#define DATA_H
#include <cstdint>

#include "eigen3/Eigen/Eigen"
#include "Structure.h"

extern const float CANVAS_W;     // length per row
extern const float CANVAS_H;     // length per col
extern const float CANVAS_Z;     // depth of pixels
extern const uint32_t PIXELS_W;  // number of pixels per row
extern const uint32_t PIXELS_H;  // number of pixels per col
extern const Eigen::Vector3f BG_COLOR;
extern const Eigen::Vector3f IA;   // Intensity of ambient light
extern const Eigen::Vector3f EYE;  // Position of eye (camera)

// Materials
extern Material material_light_blue_ball;
extern Material material_light_green_ball;
extern Material material_light_yellow_ball;
extern Material material_white_ball;
extern Material material_white_floor;
extern Material material_white_wall;
extern Material material_red;
extern Material material_blue;

void init_materials(void);

#endif  // DATA_H
