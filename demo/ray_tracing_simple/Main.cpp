#include <cstdio>
#include <ctime>
#include <iostream>
#include <list>
#include <opencv2/opencv.hpp>

#include "Data.h"
#include "Shading.h"
#include "Structure.h"

std::list<Surface *> surfaces;
std::list<PointLight *> lights;

void init_surfaces(void);
void free_surfaces(void);
void init_lights(void);
void free_lights(void);

int main(int argc, char **argv) {
    init_materials();
    init_surfaces();
    init_lights();

    // FrameBuffer & Canvas
    FrameBuffer frame_buffer(PIXELS_W, PIXELS_H);
    Canvas canvas(CANVAS_W, CANVAS_H, CANVAS_Z);

    // Raster image
    Intersection intersection;
    Intersection best_intersection;
    std::clock_t start_clock = std::clock();
    for (uint32_t row = 0; row < frame_buffer.ny; row++) {
        for (uint32_t col = 0; col < frame_buffer.nx; col++) {
            Ray view_ray = create_view_ray(canvas, frame_buffer, row, col);
            best_intersection.t = INFINITY;
            for (auto surface_ptr : surfaces) {
                if (surface_ptr->ray_hit(view_ray, &intersection, 0.1f,
                                         100.f) &&
                    intersection.t < best_intersection.t) {
                    best_intersection = intersection;
                }
            }
            if (best_intersection.t != INFINITY) {
                Eigen::Vector3f color = phong_shading(
                    best_intersection, IA, EYE, lights, surfaces, 2U, 0U);
                frame_buffer.set_color(row, col, color);
            } else {
                frame_buffer.set_color(row, col, BG_COLOR);
            }
        }
    }
    std::clock_t end_clock = std::clock();
    std::cout << "Rendering time: "
              << (end_clock - start_clock) / CLOCKS_PER_SEC << "s" << std::endl;

    // Show image
    cv::Mat img_mat(frame_buffer.ny, frame_buffer.nx, CV_32FC3,
                    frame_buffer.data);
    cv::cvtColor(img_mat, img_mat, cv::COLOR_RGB2BGR);
    cv::flip(img_mat, img_mat, 0);
    cv::imshow("Ray Tracing", img_mat);
    cv::waitKey();

    // Free resources
    free_surfaces();
    free_lights();

    return 0;
}

void init_surfaces(void) {
    Sphere *sphere_right = new Sphere;
    sphere_right->center = Eigen::Vector3f(2, -1, -8);
    sphere_right->radius = 2;
    sphere_right->material = &material_light_blue_ball;
    surfaces.push_back(sphere_right);

    Sphere *sphere_left = new Sphere;
    sphere_left->center = Eigen::Vector3f(-2, -1.5, -8);
    sphere_left->radius = 1.5;
    sphere_left->material = &material_white_ball;
    surfaces.push_back(sphere_left);

    Sphere *sphere_front = new Sphere;
    sphere_front->center = Eigen::Vector3f(0, -2, -6);
    sphere_front->radius = 1.f;
    sphere_front->material = &material_light_yellow_ball;
    surfaces.push_back(sphere_front);

    Parallelogram *floor = new Parallelogram;
    floor->origin = Eigen::Vector3f(-30, -3, 0);
    floor->dir_x = Eigen::Vector3f(60, 0, 0);
    floor->dir_y = Eigen::Vector3f(0, 0, -20);
    floor->material = &material_white_floor;
    surfaces.push_back(floor);

    Parallelogram *wall_back = new Parallelogram;
    wall_back->origin = Eigen::Vector3f(-30, -3, -10);
    wall_back->dir_x = Eigen::Vector3f(60, 0, 0);
    wall_back->dir_y = Eigen::Vector3f(0, 50, 0);
    wall_back->material = &material_white_wall;
    surfaces.push_back(wall_back);

    Parallelogram *wall_left = new Parallelogram;
    wall_left->origin = Eigen::Vector3f(-6, -3, 0);
    wall_left->dir_x = Eigen::Vector3f(0, 0, -10);
    wall_left->dir_y = Eigen::Vector3f(0, 50, 0);
    wall_left->material = &material_red;
    surfaces.push_back(wall_left);

    Parallelogram *wall_right = new Parallelogram;
    wall_right->origin = Eigen::Vector3f(6, -3, -10);
    wall_right->dir_x = Eigen::Vector3f(0, 0, 10);
    wall_right->dir_y = Eigen::Vector3f(0, 50, 0);
    wall_right->material = &material_light_green_ball;
    surfaces.push_back(wall_right);
}

void free_surfaces(void) {
    for (auto sur_ptr : surfaces) {
        delete sur_ptr;
    }
}

void init_lights(void) {
    PointLight *light_top = new PointLight;
    light_top->origin = Eigen::Vector3f(0, 7, -5);
    light_top->intensity =
        Eigen::Vector3f(255 / 255.f, 247 / 255.f, 229 / 255.f) * 5;
    lights.push_back(light_top);

    PointLight *light_0 = new PointLight;
    light_0->origin = Eigen::Vector3f(1, 1, -2);
    light_0->intensity = Eigen::Vector3f(10, 10, 10);
    lights.push_back(light_0);

    PointLight *light_1 = new PointLight;
    light_1->origin = Eigen::Vector3f(4, 4, -5);
    light_1->intensity = Eigen::Vector3f(3, 3, 3);
    lights.push_back(light_1);

    PointLight *light_2 = new PointLight;
    light_2->origin = Eigen::Vector3f(-5, 3, -4);
    light_2->intensity = Eigen::Vector3f(3, 3, 3);
    lights.push_back(light_2);
}

void free_lights(void) {
    for (auto light_ptr : lights) {
        delete light_ptr;
    }
}
