#include "Shading.h"

#include <list>

#include "Structure.h"

static bool ray_hit_surfaces(const Ray &ray, std::list<Surface *> surfaces,
                             float range_start = 0.1f, float range_end = 100.f);
static bool ray_hit_surfaces(const Ray &ray, std::list<Surface *> surfaces,
                             Intersection &result, float range_start = 0.1f,
                             float range_end = 100.f);

Ray create_othor_ray(const Canvas &canvas, const FrameBuffer &buffer,
                     uint32_t row, uint32_t col) {
    Ray result;
    float pixel_width = canvas.width / buffer.nx;
    float pixel_height = canvas.height / buffer.ny;
    float x = col * pixel_width - canvas.width / 2 + pixel_width * 0.5;
    float y = row * pixel_height - canvas.height / 2 + pixel_height * 0.5;
    result.origin = Eigen::Vector3f(x, y, 0);
    result.target = Eigen::Vector3f(x, y, canvas.z);
    return result;
}

Ray create_view_ray(const Canvas &canvas, const FrameBuffer &buffer,
                    uint32_t row, uint32_t col) {
    Ray result;
    float pixel_width = canvas.width / buffer.nx;
    float pixel_height = canvas.height / buffer.ny;
    float x = col * pixel_width - canvas.width / 2 + pixel_width * 0.5;
    float y = row * pixel_height - canvas.height / 2 + pixel_height * 0.5;
    result.origin = Eigen::Vector3f(0, 0, 0);
    result.target = Eigen::Vector3f(x, y, canvas.z);
    return result;
}

Ray create_shadow_ray(const Eigen::Vector3f &light_pos,
                      const Eigen::Vector3f &point_pos) {
    Ray result;
    result.origin = point_pos;
    result.target = light_pos;
    return result;
}

Ray create_reflection_ray(const Eigen::Vector3f &eye,
                          const Eigen::Vector3f &point_pos,
                          const Eigen::Vector3f &normal) {
    Ray result;
    result.origin = point_pos;
    Eigen::Vector3f p2e_normalized = (eye - point_pos).normalized();
    Eigen::Vector3f target_dir =
        2 * p2e_normalized.dot(normal) * normal - p2e_normalized;
    result.target = point_pos + target_dir;
    return result;
}

Eigen::Vector3f phong_shading(const Intersection &point,
                              const Eigen::Vector3f &Ia,
                              const Eigen::Vector3f &eye,
                              const std::list<PointLight *> &lights,
                              const std::list<Surface *> &surfaces,
                              uint32_t max_depth, uint32_t depth) {
    if (depth >= max_depth) return Eigen::Vector3f::Zero();
    const Material *material = &point.material;
    Eigen::Vector3f result = Ia.cwiseProduct(material->ka);
    for (auto light_ptr : lights) {
        // Shadow
        Ray shadow_ray = create_shadow_ray(light_ptr->origin, point.position);
        if (ray_hit_surfaces(shadow_ray, surfaces, 0.1f, 1.0f)) continue;

        // Point intensity
        Eigen::Vector3f point_to_light = light_ptr->origin - point.position;
        Eigen::Vector3f p2l_normalized = point_to_light.normalized();
        Eigen::Vector3f point_intensity =
            light_ptr->intensity / point_to_light.squaredNorm();

        // Diffuse term
        Eigen::Vector3f Ld = material->kd.cwiseProduct(point_intensity) *
                             std::max(0.f, point.normal.dot(p2l_normalized));

        // Specular term
        Eigen::Vector3f p2e_normalized = (eye - point.position).normalized();
        Eigen::Vector3f half_way =
            (p2l_normalized + p2e_normalized).normalized();
        Eigen::Vector3f Ls =
            material->ks.cwiseProduct(point_intensity) *
            std::pow(std::max(0.f, point.normal.dot(half_way)), material->p);

        // Refection term
        Eigen::Vector3f Lm = Eigen::Vector3f::Zero();
        if (point.material.km != Eigen::Vector3f::Zero()) {
            Ray reflection_ray =
                create_reflection_ray(eye, point.position, point.normal);
            Intersection reflect_src_point;
            if (ray_hit_surfaces(reflection_ray, surfaces, reflect_src_point,
                                 0.1f, INFINITY)) {
                Lm = phong_shading(reflect_src_point, Ia, point.position,
                                   lights, surfaces, max_depth, depth + 1)
                         .cwiseProduct(point.material.km);
            }
        }

        result += Ls + Ld + Lm;
    }
    return result;
}

bool ray_hit_surfaces(const Ray &ray, std::list<Surface *> surfaces,
                      float range_start, float range_end) {
    for (auto sur_ptr : surfaces) {
        if (sur_ptr->ray_hit(ray, nullptr, range_start, range_end)) {
            return true;
        }
    }
    return false;
}

bool ray_hit_surfaces(const Ray &ray, std::list<Surface *> surfaces,
                      Intersection &result, float range_start,
                      float range_end) {
    result.t = INFINITY;
    Intersection cur_intersection;
    for (auto sur_ptr : surfaces) {
        if (sur_ptr->ray_hit(ray, &cur_intersection, range_start, range_end) &&
            cur_intersection.t < result.t) {
            result = cur_intersection;
        }
    }
    return result.t != INFINITY;
}
