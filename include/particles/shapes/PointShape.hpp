#ifndef POINT_SHAPE_HPP
#define POINT_SHAPE_HPP

#include "particles/shapes/EmissionShape.hpp"

namespace particles
{
    class PointShape : public EmissionShape
    {
    public:
        PointShape(float x, float y);
        void setPosition(float x, float y) override;
        std::pair<float,float> sample() override;
    
    private:
        float x;
        float y;
    };

}

#endif
