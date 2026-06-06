#include "particles/shapes/PointShape.hpp"

namespace particles
{

    PointShape::PointShape(float px, float py)
    :
    x(px), y(py)
    {}

    void PointShape::setPosition(float px, float py)
    {
        x=px;
        y=py;
    }

    std::pair<float,float> PointShape::sample()
    {
        return {x, y};
    }

}