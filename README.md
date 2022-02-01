# Simple Rendering

This repository is made for personal learning purpose. It contains:

1. A simple rasterizer (mimicking GPU pipeline)
2. A simple whitted-style ray tracing algorithm
3. Some demo's built on top of 1 and 2

This project is evolving and implementations in different demo's can vary dramatically.

## Demo's

|         Folder          |        Target         | Description                                                |
| :---------------------: | :-------------------: | :--------------------------------------------------------- |
|      render_simple      |     demo_triangle     | Simple triangle with color interpolation                   |
|    render_transform     |    demo_transform     | A cube and a camera with "AWSD" movement interaction       |
|      render_shader      |      demo_shader      | A demo using the shader class                              |
|     render_texture      |  demo_simple_texture  | Spinning texture with corrected uv and bilinear lerp       |
|   ray_tracing_simple    |  ray_tracing_simple   | Whitted-style ray tracing demo                             |
| render_uv_interpolation | demo_uv_interpolation | Use grid texture to verify corrected uv                    |
|      render_mipmap      |      demo_mipmap      | Trilinear mipmap filtering                                 |
|    render_obj_loader    |    demo_obj_loader    | Test wavefront obj loader (torus)                          |
|    render_framework     |    demo_framework     | Use the general rasterizing framework (coding in one file) |

## Dependency

1. OpenCV 4.5
2. Eigen
