#ifndef BILINEARTEXTURE_H
#define BILINEARTEXTURE_H
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include "core/Texture.h"

class BilinearTexture : public ITexture {
   public:
    Eigen::Vector3f sample(float u, float v) const override;

    cv::Mat *image_{nullptr};
};

#endif  // BILINEARTEXTURE_H
