#include "Data.h"

const float CANVAS_W = 9 * 0.7f;
const float CANVAS_H = 6 * 0.7f;
const float CANVAS_Z = -3;
const uint32_t PIXELS_W = 600;
const uint32_t PIXELS_H = 400;
const Eigen::Vector3f BG_COLOR = Eigen::Vector3f::Ones();
const Eigen::Vector3f IA =
    Eigen::Vector3f::Ones() * 0.4;  // Ambient light intensity
const Eigen::Vector3f EYE = Eigen::Vector3f(0, 0, 0);

Material material_light_blue_ball;
Material material_light_green_ball;
Material material_light_yellow_ball;
Material material_white_ball;
Material material_white_floor;
Material material_white_wall;
Material material_red;
Material material_blue;

void init_materials(void) {
    material_light_blue_ball.kd =
        Eigen::Vector3f(77 / 255.f, 210 / 255.f, 255 / 255.f);
    material_light_blue_ball.ks =
        Eigen::Vector3f(77 / 255.f, 210 / 255.f, 255 / 255.f) * 0.5f;
    material_light_blue_ball.ka =
        Eigen::Vector3f(77 / 255.f, 210 / 255.f, 255 / 255.f);
    material_light_blue_ball.km = Eigen::Vector3f::Zero();
    material_light_blue_ball.p = 10000;

    material_light_green_ball.kd =
        Eigen::Vector3f(112 / 255.f, 219 / 255.f, 112 / 255.f);
    material_light_green_ball.ks = Eigen::Vector3f(1, 1, 1) * 0.5f;
    material_light_green_ball.ka =
        Eigen::Vector3f(112 / 255.f, 219 / 255.f, 112 / 255.f);
    material_light_green_ball.km = Eigen::Vector3f::Ones() * 0.01f;
    material_light_green_ball.p = 10000;

    material_light_yellow_ball.kd =
        Eigen::Vector3f(254 / 255.f, 255 / 255.f, 153 / 255.f) * 0.9f;
    material_light_yellow_ball.ks =
        Eigen::Vector3f(254 / 255.f, 255 / 255.f, 153 / 255.f) * 0.2f;
    material_light_yellow_ball.ka =
        Eigen::Vector3f(254 / 255.f, 255 / 255.f, 153 / 255.f);
    material_light_yellow_ball.km = Eigen::Vector3f::Ones() * 0.01f;
    material_light_yellow_ball.p = 10000;

    material_white_ball.kd = Eigen::Vector3f::Ones();
    material_white_ball.ks = Eigen::Vector3f::Ones() * 0.5f;
    material_white_ball.ka = Eigen::Vector3f::Ones() * 0.9f;
    material_white_ball.km = Eigen::Vector3f::Ones() * 0.025f;
    material_white_ball.p = 10000;

    material_white_floor.kd = Eigen::Vector3f(1, 1, 1);
    material_white_floor.ks = Eigen::Vector3f(1, 1, 1) * 0.05f;
    material_white_floor.ka = Eigen::Vector3f(1, 1, 1);
    material_white_floor.km = Eigen::Vector3f::Ones() * 0.05;
    material_white_floor.p = 10000;

    Eigen::Vector3f wall_back_base_color(1, 1, 1);
    material_white_wall.kd = wall_back_base_color;
    material_white_wall.ks = wall_back_base_color;
    material_white_wall.ka = wall_back_base_color;
    material_white_wall.km = Eigen::Vector3f::Zero();
    material_white_wall.p = 10000;

    material_red.kd = Eigen::Vector3f(1, 0, 0);
    material_red.ks = Eigen::Vector3f(1, 1, 1);
    material_red.ka = Eigen::Vector3f(1, 0, 0);
    material_red.km = Eigen::Vector3f::Zero();
    material_red.p = 10000;

    material_blue.kd = Eigen::Vector3f(0, 0, 1);
    material_blue.ks = Eigen::Vector3f(1, 1, 1);
    material_blue.ka = Eigen::Vector3f(0, 0, 1);
    material_blue.km = Eigen::Vector3f::Zero();
    material_blue.p = 150;
}
