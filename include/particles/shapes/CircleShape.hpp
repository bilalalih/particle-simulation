#ifndef CIRCLE_SHAPE_HPP
#define CIRCLE_SHAPE_HPP

#include "particles/shapes/EmissionShape.hpp"

namespace particles
{
    class CircleShape : public EmissionShape
    {
    public:

        CircleShape(float x, float y, float r);
        void setPosition(float x, float y) override;
        
        std::pair<float,float> sample() override;
        
    private:
        float x;
        float y;
        float radius;
    };
}

#endif
