#ifndef STRUCT_H
#define STRUCT_H
#include <list>

#include "eigen3/Eigen/Eigen"
#define CHENNEL_R 0
#define CHENNEL_G 1
#define CHENNEL_B 2
class Ray;
class Intersection;
class Surface;
class Triangle;
class Sphere;
class Parallelogram;
class FrameBuffer;
class Rasterizer;
class PointLight;
class Material;

class Ray {
   public:
    Eigen::Vector3f origin;
    Eigen::Vector3f target;
};

class Material {
   public:
    Eigen::Vector3f ka;  // ambient coefficient in [0, 1]^3
    Eigen::Vector3f kd;  // diffuse color in [0, 1]^3
    Eigen::Vector3f ks;  // specular coefficient in [0, 1]^3
    Eigen::Vector3f km;  // mirror reflection
    float p;             // phong exponent
};

class Intersection {
   public:
    Eigen::Vector3f position;
    Eigen::Vector3f normal;
    float t;  // ray coefficient
    Material material;
};

class Surface {
   public:
    virtual bool ray_hit(const Ray &ray, Intersection *result,
                         float range_start = 0.1f, float range_end = 100.f) = 0;
    virtual ~Surface() = default;
};

class Triangle : public Surface {
   public:
    bool ray_hit(const Ray &ray, Intersection *result, float range_start = 0.1f,
                 float range_end = 100.f) override;

    Eigen::Vector3f v0;
    Eigen::Vector3f v1;
    Eigen::Vector3f v2;
    Eigen::Vector3f color0;
    Eigen::Vector3f color1;
    Eigen::Vector3f color2;
    Material *material{nullptr};
};

class Sphere : public Surface {
   public:
    bool ray_hit(const Ray &ray, Intersection *result, float range_start = 0.1f,
                 float range_end = 100.f) override;

    Eigen::Vector3f center;
    float radius;
    Material *material;
};

class Parallelogram : public Surface {
   public:
    bool ray_hit(const Ray &ray, Intersection *result, float range_start = 0.1f,
                 float range_end = 100.f) override;

    Eigen::Vector3f origin;
    Eigen::Vector3f dir_x;
    Eigen::Vector3f dir_y;
    Material *material{nullptr};
};

class FrameBuffer {
   public:
    uint32_t nx;  // pixels per row; number of cols
    uint32_t ny;  // pixels per col; number of rows
    float *data;  // pixel starts from lower-left corner, in row-major order

    FrameBuffer(uint32_t nx, uint32_t ny) : nx(nx), ny(ny) {
        data = new float[nx * ny * 3];
    }

    float get_color(uint32_t row, uint32_t col, uint32_t chennel) {
        return data[3 * (row * nx + col) + chennel];
    }

    void set_color(uint32_t row, uint32_t col, const Eigen::Vector3f &color) {
        uint32_t base = 3 * (row * nx + col);
        data[base + 0] = color.x();
        data[base + 1] = color.y();
        data[base + 2] = color.z();
    }

    ~FrameBuffer() { delete[] data; }
};

class Canvas {
   public:
    Canvas(float width, float height, float z)
        : width(width), height(height), z(z) {}

    float width;
    float height;
    float z;
};

class Rasterizer {
   public:
    Rasterizer(uint32_t nx, uint32_t ny) : buffer(nx, ny) {}

    std::list<Surface *> surfaces;
    FrameBuffer buffer;
};

class PointLight {
   public:
    Eigen::Vector3f origin;
    Eigen::Vector3f intensity;  // intensity at one unit length for each channel
};

#endif  // STRUCT_H
