#ifndef NULLPRIMITIVE_H
#define NULLPRIMITIVE_H

#include "core/Primitive.h"
#include "core/Color.h"

class NullPrimitive : public IPrimitive {
    [[nodiscard]] virtual BoundingBox get_bbox() const override {
        return BoundingBox();
    };
    virtual void set_cursor(float x, float y) override{};
    [[nodiscard]] virtual float interpolated_z() const override { return 0; };
    [[nodiscard]] virtual bool is_inside() const override { return false; };
    [[nodiscard]] virtual Eigen::Vector3f get_color() const override {
        return COLOR_BLACK;
    };
};

#endif  // NULLPRIMITIVE_H
