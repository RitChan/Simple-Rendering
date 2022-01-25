#include "texture_impl/BilinearTexture.h"


Eigen::Vector3f BilinearTexture::sample(float u, float v) const {
    float x = u * image_->cols - 0.5f;
    float y = v * image_->rows - 0.5f;
    float x0 = std::floor(x);
    float y0 = std::floor(y);
    float x1 = x0 + 1;
    float y1 = y0 + 1;
    float u0 = x - x0;
    float u1 = x1 - x;
    float v0 = y - y0;
    float v1 = y1 - y;
    int px0 = (int)std::max(0.f, x0);
    int py0 = (int)std::max(0.f, y0);
    int px1 = (int)std::min((float)image_->cols-1, x1);
    int py1 = (int)std::min((float)image_->rows-1, y1);
    auto tx00 = image_->at<cv::Vec3b>(py0, px0);
    auto tx10 = image_->at<cv::Vec3b>(py0, px1);
    auto tx01 = image_->at<cv::Vec3b>(py1, px0);
    auto tx11 = image_->at<cv::Vec3b>(py1, px1);
    auto tx = u0 * v0 * tx00 + u0 * v1 * tx01 + u1 * v0 * tx10 + u1 * v1 * tx11;
    return Eigen::Vector3f(tx[0] / 255.f, tx[1] / 255.f, tx[2] / 255.f);
}