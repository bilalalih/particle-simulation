#ifndef RECT_SHAPE_HPP
#define RECT_SHAPE_HPP

#include "particles/shapes/EmissionShape.hpp"

namespace particles
{
    class RectShape : public EmissionShape
    {
    public:
        RectShape(float x, float y, float width, float height);

        void setPosition(float x, float y) override;
        std::pair<float, float> sample() override;

    private:
        float x;
        float y;
        float width;
        float height;
    };
}

#endif
