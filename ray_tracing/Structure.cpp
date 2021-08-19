#include "Structure.h"

static bool inrange(float val, float range_start, float range_end);

bool Triangle::ray_hit(const Ray &ray, Intersection *result, float range_start,
                       float range_end) {
    // Solve Ax = b
    // where (x.x(), x.y(), x.z()) is the barycentric coordinate
    // and x.w() is ray coefficient
    Eigen::Matrix4f A;
    A << v0.x(), v1.x(), v2.x(), ray.target.x(), v0.y(), v1.y(), v2.y(),
        ray.target.y(), v0.z(), v1.z(), v2.z(), ray.target.z(), 1, 1, 1, 0;
    if (A.determinant() == 0) return false;
    Eigen::Vector4f b(ray.origin.x(), ray.origin.y(), ray.origin.z(), 1);
    Eigen::Vector4f x = A.inverse() * b;
    if (x.x() < 0 || x.y() < 0 || x.z() < 0) return false;
    if (-x.w() < range_start || -x.w() >= range_end) return false;
    if (result == nullptr) return true;
    result->t = -x.w();
    result->position = ray.origin - x.w() * ray.target;
    result->material.kd = x.x() * color0 + x.y() * color1 + x.z() * color2;
    result->material.ka = material->ka;
    result->material.ks = material->ks;
    result->material.p = material->p;
    return true;
}

bool Sphere::ray_hit(const Ray &ray, Intersection *result, float range_start,
                     float range_end) {
    // Solve Ax^2 + Bx + C = 0 where x is the ray parameter
    Eigen::Vector3f ray_orient = ray.target - ray.origin;
    float A = ray_orient.squaredNorm();
    if (A == 0) return false;  // ignore A == 0
    float B = 2 * ray_orient.dot(ray.origin - center);
    float C = center.squaredNorm() - radius * radius -
              2 * center.dot(ray.origin) + ray.origin.squaredNorm();
    float det = B * B - 4 * A * C;
    if (det < 0) return false;
    float sqrt_det = std::sqrt(det);
    float two_A = 2 * A;
    float x1 = (-B - sqrt_det) / two_A;
    float x2 = (-B + sqrt_det) / two_A;
    float x;
    bool x1_inrange = inrange(x1, range_start, range_end);
    bool x2_inrange = inrange(x2, range_start, range_end);
    if (!x1_inrange && !x2_inrange) {
        return false;
    } else if (!x1_inrange && x2_inrange) {
        x = x2;
    } else if (x1_inrange && !x2_inrange) {
        x = x1;
    } else {
        x = std::min(x1, x2);
    }
    if (x < range_start || x >= range_end) return false;
    if (result == nullptr) return true;
    result->t = x;
    result->position = ray.origin + x * ray_orient;
    result->normal = (result->position - center).normalized();
    result->material = *material;
    return true;
}

bool Parallelogram::ray_hit(const Ray &ray, Intersection *result,
                            float range_start, float range_end) {
    // Solve Ax = b
    Eigen::Vector3f ray_orient = ray.target - ray.origin;
    Eigen::Matrix3f A;
    A << -ray_orient.x(), dir_x.x(), dir_y.x(), -ray_orient.y(), dir_x.y(),
        dir_y.y(), -ray_orient.z(), dir_x.z(), dir_y.z();
    if (A.determinant() == 0) return false;
    Eigen::Vector3f b = ray.origin - origin;
    Eigen::Vector3f x = A.inverse() * b;
    if (x.y() < 0 || x.y() >= 1 || x.z() < 0 || x.z() >= 1)
        return false;
    if (x.x() < range_start || x.x() >= range_end) return false;
    if (result == nullptr) return true;
    result->t = x.x();
    result->normal = dir_x.cross(dir_y).normalized();
    result->position = ray.origin + result->t * ray_orient;
    result->material = *material;
    return true;
}

inline bool inrange(float val, float range_start, float range_end) {
    return range_start <= val && val < range_end;
}
