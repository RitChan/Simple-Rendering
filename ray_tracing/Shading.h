#ifndef SHADING_H
#define SHADING_H

#include "eigen3/Eigen/Eigen"
#include "Structure.h"

Ray create_othor_ray(const Canvas &canvas, const FrameBuffer &buffer,
                     uint32_t row, uint32_t col);
Ray create_view_ray(const Canvas &canvas, const FrameBuffer &buffer,
                    uint32_t row, uint32_t col);
Ray create_shadow_ray(const Eigen::Vector3f &light_pos,
                      const Eigen::Vector3f &point_pos);
Ray create_reflection_ray(const Eigen::Vector3f &eye,
                          const Eigen::Vector3f &point_pos,
                          const Eigen::Vector3f &normal);
Eigen::Vector3f phong_shading(const Intersection &point,
                              const Eigen::Vector3f &Ia,
                              const Eigen::Vector3f &eye,
                              const std::list<PointLight *> &lights,
                              const std::list<Surface *> &surfaces,
                              uint32_t max_depth = 3, uint32_t depth = 0);
#endif  // SHADING_H
