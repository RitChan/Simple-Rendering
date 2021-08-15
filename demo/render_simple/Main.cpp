//
// Created by Ritee on 2021/8/8.
//
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include <vector>

#include "RenderingCore.h"
#include "SimpleRenderer.h"
#include "primitive_impl/SimpleTriangle.h"
#include "rasterizer_impl/SimpleRasterizer.h"

using namespace std;
using namespace Eigen;

int main() {
    SimpleRenderer renderer;
    TriangleMesh mesh;
    SimpleRasterizer rasterizer(600, 400);
    renderer.mesh_ = &mesh;
    renderer.rasterizer_ = &rasterizer;

    mesh.vertices = vector<Vector3f>{
        Vector3f(100, 100, 0), Vector3f(300, 100, 0), Vector3f(200, 300, 0)};

    mesh.colors = vector<Vector3f>{COLOR_RED, COLOR_GREEN, COLOR_BLUE};

    mesh.indices = vector<Vector3i>{{0, 1, 2}};

    mesh.world_mat = Matrix4f::Identity();
    renderer.view_ = Matrix4f::Identity();
    renderer.projection_ = Matrix4f::Identity();
    renderer.viewport_ = Matrix4f::Identity();

    renderer.render();
    return 0;
}